#!/usr/bin/python
#-*- coding: utf-8 -*-

### Packet types ###

PACKET_HELLO  = 0x01
PACKET_PING   = 0x02
PACKET_PONG   = 0x03
PACKET_GET    = 0x04
PACKET_SET    = 0x05
PACKET_VALUES = 0x06

### Read packet ###

def getPacketSrc(message):
	return ord(message[0])

def getPacketDest(message):
	return ord(message[1])

def getPacketRouter(message):
	return ord(message[2])

def getPacketType(message):
	return ord(message[3])

def getPacketCounter(message):
	return readInteger(message[4:6])

def getPacketData(message):
	return message[6:]

### Parse data ###

def readValues(data):
	values = []
	while len(data) > 3:
		srcDevice = ord(data[0])
		destDevice = ord(data[1])
		valueType = data[2]
		value = None
		if valueType == 'I':
			value = readInteger(data[3:5])
			data = data[5:]
		elif valueType == 'S':
			count = ord(data[3])
			value = data[4:4+count]
			data = data[4+count:]
		else:
			break
		values.append((srcDevice, destDevice, value))
	return values

def writeValues(values):
	data = ""
	for (srcDeviceId, destDeviceId, value) in values:
		data += chr(srcDeviceId)
		data += chr(destDeviceId)
		if type(value) is int:
			data += 'I' + writeInteger(value)
		elif type(value) is str:
			data += 'S' + chr(len(value)) + value
	return data

def writeDevices(devices):
	data = ""
	for (srcDeviceId, destDeviceId) in devices:
		data += chr(srcDeviceId)
		data += chr(destDeviceId)
	return data

### Send packet ###

def hello(sniffer):
	sniffer.send(buildPacket(0xFF, PACKET_HELLO))

def ping(destNodeId, sniffer):
	sniffer.send(buildPacket(destNodeId, PACKET_PING))

def pong(destNodeId, sniffer):
	sniffer.send(buildPacket(destNodeId, PACKET_PONG))

def setValue(destNodeId, srcDeviceId, destDeviceId, value, sniffer):
	data = writeValues([(srcDeviceId, destDeviceId, value),(0xFF,0xFF,0)])
	sniffer.send(buildPacket(destNodeId, PACKET_SET, data=data))

def getValue(destNodeId, srcDeviceId, destDeviceId, sniffer):
	data = writeDevices([(srcDeviceId, destDeviceId),(0xFF,0xFF)])
	sniffer.send(buildPacket(destNodeId, PACKET_GET, data=data))

### TOOLS ###

# return packet formatted according bugOne protocol (do not send)
# packetType can be: 1 Hello, 2 Ping, 3 Pong, 4 Get, 5 Set, 6 Values
def buildPacket(destNodeId, packetType, srcNodeId = 0, lastCounter = 0, data = None):
	message  = chr(srcNodeId)   # Src
	message += chr(destNodeId)  # Dest
	message += chr(0)           # Router
	message += chr(packetType)  # Type
	message += writeInteger(lastCounter) # Counter
	if data:
		message += data
	return message

def readInteger(bytes, bigEndian = True):
	res = 0
	if bigEndian: bytes = bytes[::-1]
	for b in bytes:
		res = res << 8
		res += ord(b)
	return res

def writeInteger(value):
	return chr(value & 0x00FF) + chr((value & 0xFF00) >> 8)

