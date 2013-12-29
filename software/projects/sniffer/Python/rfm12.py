#!/usr/bin/python
#-*- coding: utf-8 -*-

import serial

# Simple class to handle messages from RFM12 sniffer
class SnifferSerial:

	def __init__(self, device="/dev/ttyUSB0", baudrate=38400):
		self.port = serial.Serial(device, baudrate, timeout=1)

	def close(self):
		if self.port:
			self.port.close()

	# return None on error, message data else
	def waitForMessage(self):
		buf = self.port.read(1)
		if (len(buf) != 1):
			return None
		size = ord(buf)
		data = self.port.read(size)
		if (len(data) != size):
			return None
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
		self.port.write(chr(len(message)) + message)
		self.port.flush()

import socket

class SnifferEthernet:
	port = 1234

	def __init__(self, bugone):
		self.socket = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
		self.bugone = bugone

	def close(self):
		self.socket.close()

	def waitForMessage(self):
		self.socket.bind((self.bugone,self.port))
		data, adrr = self.socket.recvfrom(256)
		return data

	def send(self, message):
		if len(message) > 255:
			raise Exception("Message is too long")
		sock.sendto(message,(self.bugone,self.port))
