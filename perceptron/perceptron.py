# -*- coding: utf-8 -*-

class Perceptron(object):
  def __init__(self, dim, eta):
    self._w = [0] * dim
    self._eta = eta

  def train(self, t, v):
    o = int(t) - self.feed_forward(v)
    for i in range(len(v)):
      self._w[i] += v[i] * o * self._eta

  def feed_forward(self, v):
    return self._step(self._inp(v, self._w))

  @staticmethod
  def _inp(v1, v2):
    assert(len(v1) == len(v2))
    inp = 0
    for i in range(len(v1)):
      inp += v1[i] * v2[i]
    return inp

  @staticmethod
  def _step(x):
    return 1 if x > 0 else 0
