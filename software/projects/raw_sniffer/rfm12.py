#!/usr/bin/python
#-*- coding: utf-8 -*-

import serial

# Simple class to handle messages from RFM12 sniffer
class Sniffer:

	def __init__(self, device="/dev/ttyUSB0", baudrate=38400):
		self.port = serial.Serial(device, baudrate)

	def close(self):
		if self.port:
			self.port.close()

	# return None on error, message data else
	def waitForMessage(self):
		size = ord(self.port.read())
		data = self.port.read(size)
		checksum = ord(self.port.read())
		c = 0
		for i in data:
			c ^= ord(i)
		if checksum != c:
			return None
		else:
			return data

	# send data, throw an exception if size is superior 255
	def send(self, message):
		if len(message) > 255:
			raise Exception("Message is too long")
		self.port.write(chr(len(message)))
		self.port.write(message)
		self.port.flush()

