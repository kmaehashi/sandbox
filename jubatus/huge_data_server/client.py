#!/usr/bin/env python
# -*- coding: utf-8 -*-

import msgpackrpc

port = 9199
timeout = 1

while True:
  try:
    print '.',
    c = msgpackrpc.Client(msgpackrpc.Address("127.0.0.1", port), timeout)
    c.call("get_config", "")
    raise RuntimeError()
  except msgpackrpc.error.TimeoutError:
    pass
  finally:
    c.close()
