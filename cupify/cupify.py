#!/usr/bin/env python3

import sys

import numpy
import cupy


modules = sys.modules
for name in modules.keys():
    if name == 'numpy' or name.startswith('numpy.'):
        name_cupy = name.replace('numpy', 'cupy', 1)
        if name_cupy in modules:
            print(f'patch: {name}')
            modules[name] = modules[name_cupy]


with open(sys.argv[1]) as f:
    exec(f.read())
