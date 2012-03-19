#!/usr/bin/python
#-*- coding: utf-8 -*-

import rfm12
import bugOne

import sys
device = "/dev/ttyUSB0"
if len(sys.argv) == 2:
	device = sys.argv[1]

sniffer = rfm12.SnifferSerial(device)

bugOne.ping(0x1, sniffer)

while True:
	message = sniffer.waitForMessage()
	if message:
		messageType = bugOne.getPacketType(message)
		srcNodeId = bugOne.getPacketSrc(message)
		destNodeId = bugOne.getPacketDest(message)
		counter = bugOne.getPacketCounter(message)
		print "Message [%s] from %s to %s" % (counter, hex(srcNodeId), hex(destNodeId))
		if messageType == bugOne.PACKET_HELLO:
			print "Hello"
		elif messageType == bugOne.PACKET_PING:
			print "Ping"
		elif messageType == bugOne.PACKET_PONG:
			print "Pong"
		elif messageType == bugOne.PACKET_VALUES:
			values = bugOne.readValues(bugOne.getPacketData(message))
			for (srcDevice, destDevice, value) in values:
				print "- (%s.%s) -> (%s.%s) = %s" % \
					(srcNodeId, srcDevice, destNodeId, destDevice, value)
		else:
			print [hex(ord(i)) for i in bugOne.getPacketData(message)]
	else:
		sys.stdout.write(".")
		sys.stdout.flush()

