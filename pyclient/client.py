#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket
import time
import sys

def connects(ss):
    s = socket.socket()
    #host = socket.gethostname()
    port = 22222

    s.connect(("0.0.0.0", port))
    s.send(str(ss))
    print s.recv(1024)
    s.close()
    time.sleep(2)
i = 0
while i < 10:
    connects(sys.argv[1])
