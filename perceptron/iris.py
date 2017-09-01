#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random

from perceptron import Perceptron
from dataset import *

p = Perceptron(4, 0.0001)

for s, v in zip(iris_setosa, iris_versicolor):
  p.train(1, s)
  p.train(0, v)
  #p.train(random.randint(0,1), s)
  #p.train(random.randint(0,1), v)

(total, ok) = (0, 0)
ok = 0
for s, v in zip(iris_setosa, iris_versicolor):
  ok += int(p.feed_forward(s) == 1)
  ok += int(p.feed_forward(v) == 0)
  total += 2

print(total)
print(ok)
print(p._w)
