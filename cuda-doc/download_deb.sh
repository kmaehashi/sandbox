#!/bin/bash

rm -rf usr

VERSIONS="
ubuntu1404:6-5_6.5-19
ubuntu1404:7-0_7.0-28
ubuntu1404:7-5_7.5-18
ubuntu1604:8-0_8.0.61-1
ubuntu1604:9-0_9.0.176-1
ubuntu1604:9-1_9.1.85-1
ubuntu1604:9-2_9.2.88-1
"

for REPO_VER in ${VERSIONS}; do
    REPO="$(echo ${REPO_VER} | cut -d: -f1)"
    VER="$(echo ${REPO_VER} | cut -d: -f2)"
    FILENAME="cuda-documentation-${VER}_amd64.deb"
    (
        if [ ! -f "${FILENAME}" ]; then
            echo "Downloading ${FILENAME}..."
            curl --fail -o "${FILENAME}" "http://developer.download.nvidia.com/compute/cuda/repos/${REPO}/x86_64/${FILENAME}"
        fi
        echo "Extracting ${FILENAME}..."
        dpkg -x "${FILENAME}" .
    ) &
done

wait
