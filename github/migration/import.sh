#!/bin/bash

# Usage:
#   ./import.sh https://ghe.example.com/srcorg/testrepo destorg testrepo https://web.example.com/git_archive.tar.gz https://web.example.com/meta_archive.tar.gz
# Assumes GH_TOKEN (admin:org, delete_repo, repo, workflow).

set -uex

src_url=$1
dest_org=$2
dest_repo=$3
archive_git=$4
archive_meta=$5

gh repo delete ${dest_org}/${dest_repo} || true

cd "$(dirname "${0}")"

dest_org_id="$(gh api "/orgs/${dest_org}" --jq '.node_id')"

out_01=$(gh api graphql -fquery="$(cat 01_create_migration_source.graphql)" -Fname="GHEC Source" -Furl="https://github.com" -Ftype="GITHUB_ARCHIVE" -FownerId="${dest_org_id}")
echo "${out_01}"
mig_source_id=$(echo "${out_01}" | jq -r .data.createMigrationSource.migrationSource.id)

out_02="$(gh api graphql -fquery="$(cat 02_start_repository_migration.graphql)" -FsourceId="${mig_source_id}" -FownerId="${dest_org_id}" -FsourceRepositoryUrl="${src_url}" -FrepositoryName="$(basename ${src_url})" -FcontinueOnError=true -FgitArchiveUrl="${archive_git}" -FmetadataArchiveUrl="${archive_meta}" -FaccessToken="${GH_TOKEN}" -FgithubPat="${GH_TOKEN}" -FskipReleases=false -FtargetRepoVisibility=private -FlockSource=false)"

echo "${out_02}"
mig_id="$(echo "${out_02}" | jq -r .data.startRepositoryMigration.repositoryMigration.id)"

while :; do
  sleep 5
  gh api graphql -fquery="$(cat 03_query_status.graphql)" -Fid="${mig_id}"
done
