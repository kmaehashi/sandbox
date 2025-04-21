# GitHUb migration with trimming oversized metadata archive

```
# Extract meta archive
tar xf meta_archive.tar.gz --one-top-level
mkdir meta_out meta_trimmed

# Create trimming plan
python ./trim_attachments.py meta_archive meta_out > trim.log

# Use commands shown in trim.log to rm or mv oversized attachments and merge meta_out onto meta_archive

# Ensure the total size fits within 20GB limit
du -csh meta_archive

# Rre-create archive
tar -C meta_archive -c -z -f meta_archive_trimmed.tar.gz .

# Let gh-gei do the rest
export GH_PAT=ghp_XXXXXXXXXXXXXXXXXXXXXXXXXX
export AWS_ACCESS_KEY_ID=XXXXXXXXXXXXXXX
export AWS_SECRET_ACCESS_KEY=XXXXXXXXXXXXXXX

gh gei migrate-repo \
--github-source-org ORG \
--source-repo REPO \
--github-target-org ORG \
--target-repo REPO \
--git-archive-path git_archive.tar.gz \
--metadata-archive-path meta_archive_trimmed.tar.gz \
--target-repo-visibility private \
--aws-bucket-name BUCKETNAME \
--aws-region ap-northeast-1
```
