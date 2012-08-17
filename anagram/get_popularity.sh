#!/bin/sh

for WORD in $(cat out.txt); do
    echo -n "${WORD} ";
    curl -s "http://ajax.googleapis.com/ajax/services/search/web?v=1.0&q=${WORD}" | 
        perl -pe 'm/"estimatedResultCount":"(\d+)"/; print $1; exit';
    echo;
done

