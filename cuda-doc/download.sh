#!/bin/sh

rm -rf usr


VERSIONS="
7-0-7.0-28
7-5-7.5-18
8-0-8.0.61-1
9-0-9.0.176-1
9-1-9.1.85-1
"

for VER in ${VERSIONS}; do
    FILENAME="cuda-documentation-${VER}.x86_64.rpm"
    # curl -o "${FILENAME}" "http://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/${FILENAME}"
    ( rpm2cpio "${FILENAME}" | cpio -id ) &
done
wait

