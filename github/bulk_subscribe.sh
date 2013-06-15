#!/bin/bash -ue

GH_USER="kmaehashi"
URLS=""
while read REPO; do URLS="${URLS} https://api.github.com/repos/${REPO}/subscription"; done << '_EOF_'
LyricsMaster/macoslib
msgpack/msgpack-rpc
# ... list repos here ...
_EOF_

curl --request PUT --data '{"subscribed": "true"}' --user "${GH_USER}" ${URLS}
