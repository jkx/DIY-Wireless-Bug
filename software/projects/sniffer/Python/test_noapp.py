#!/usr/bin/python
#-*- coding: utf-8 -*-

import rfm12

import sys
device = "/dev/ttyUSB0"
if len(sys.argv) == 2:
	device = sys.argv[1]

sniffer = rfm12.SnifferSerial(device)

while True:
	sniffer.send("Hello")
	message = sniffer.waitForMessage()
	if message:
		print [hex(ord(i)) for i in message], message
	else:
		sys.stdout.write(".")
		sys.stdout.flush()

