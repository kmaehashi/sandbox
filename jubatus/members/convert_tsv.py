#!python

import csv

tsv = csv.reader(file(r"data.tsv"), delimiter = '\t', )

headers = ['name','photo','role','expertise','contrib','github','twitter','web','blog','email']

for line in tsv:
    print ".. jubamember::"
    for i in range(len(line)):
        if line[i]:
            print "  :" + headers[i] + ": " + line[i]
    print ""
