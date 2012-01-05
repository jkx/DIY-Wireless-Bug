#!/usr/bin/python
#-*- coding: utf-8 -*-

import sys
import rfm12
import bugOne

if len(sys.argv) != 2:
	print >>sys.stderr, "usage:", sys.argv[0], "<value>"
	exit(1)

sniffer = rfm12.Sniffer()

bugOne.setValue(0x16, 0, 2, int(sys.argv[1]), sniffer)
