#!/bin/sh

# Automatic ICON Extractor
# @author Kenichi Maehashi

# Note: wrestool command from icoutils package required.

extract_icons() {
  TARGET="${1}"
  OUTDIR="${1}_resources"

  mkdir "${OUTDIR}"

  COUNT=0
  wrestool -l --all "${TARGET}" | while read ARGS; do
    COUNT="$((${COUNT} + 1))"
    echo -n "Processing #${COUNT}... "
    wrestool -x ${ARGS%%\[*\]*} -o "${OUTDIR}/${COUNT}.unknown" "${TARGET}"
    FILETYPE="$(file "${OUTDIR}/${COUNT}.unknown")"
    if echo "${FILETYPE}" | grep -q "PNG image data"; then
      echo -n "** PNG **"
      mv "${OUTDIR}/${COUNT}.unknown" "${OUTDIR}/${COUNT}.png"
    elif echo "${FILETYPE}" | grep -q "MS Windows icon resource"; then
      echo -n "** ICO **"
      mv "${OUTDIR}/${COUNT}.unknown" "${OUTDIR}/${COUNT}.ico"
    else
      echo "Unknown"
    fi
    echo " (${FILETYPE})"
  done
}

main() {
  for FILE in "$@"; do
    extract_icons "${FILE}"
  done
}

main "$@"
