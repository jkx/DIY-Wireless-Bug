#!/usr/bin/python
#-*- coding: utf-8 -*-

import sys
import rfm12
import bugOne

if len(sys.argv) != 2:
	print >>sys.stderr, "usage:", sys.argv[0], "<device id (int)>"
	exit(1)

sniffer = rfm12.Sniffer()

destDeviceId = int(sys.argv[1])
print "Ping", hex(destDeviceId)
bugOne.ping(destDeviceId, sniffer)
message = sniffer.waitForMessage()

if message and bugOne.getPacketType(message) == bugOne.PACKET_PONG:
	print "Pong"
else:
	print "Error"
