#!/usr/bin/env python

import sys
from os.path import basename

for line in sys.stdin:
  line = line.rstrip()
  if line:
    (path, flag) = line.split('\t', 1)
    sys.stdout.write(flag + '\t' + ('\t' * path.count('/')) + basename(path) + '\n')
