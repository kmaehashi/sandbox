#!/bin/bash

# Assumes GH_HOST (if GHES) and GH_TOKEN (admin:org, repo).

set -uex

src_org=$1
src_repo=$2

# Git data
cat << _EOF_ | gh api '/orgs/${src_org}/migrations' --input -
{"repositories":["${src_repo}"],"exclude_metadata":true}
_EOF_

# Metadata
cat << _EOF_ | gh api '/orgs/${src_org}/migrations' --input -
{"repositories":["${src_repo}"],"exclude_git_data":true,"exclude_releases":false,"lock_repositories":false,"exclude_owner_projects":true}
_EOF_

# Wait, then download
# gh api /orgs/${src_org}/migrations/${MIGRATION_GIT_ID}/archive > git_archive.tar.gz
# gh api /orgs/${src_org}/migrations/${MIGRATION_META_ID}/archive > meta_archive.tar.gz
