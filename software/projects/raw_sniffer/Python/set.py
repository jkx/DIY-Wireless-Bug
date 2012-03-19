#!/usr/bin/python
#-*- coding: utf-8 -*-

import sys
import rfm12
import bugOne

if len(sys.argv) != 2:
	print >>sys.stderr, "usage:", sys.argv[0], "<value>"
	exit(1)

sniffer = rfm12.SnifferSerial()

bugOne.setValue(0x1, 0, 1, int(sys.argv[1]), sniffer)
