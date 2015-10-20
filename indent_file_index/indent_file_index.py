#!/usr/bin/env python

import sys
from os.path import basename

for line in sys.stdin:
  sys.stdout.write(('\t' * line.count('/')) + basename(line))
