#!/usr/bin/python
#-*- coding: utf-8 -*-

PACHUBE_API_KEY="KQ72sqMF8EajH1SeXMDGYOr63nsQQEEdA_gH-QqmYFQ"


### PACHUBE ###
import urllib2
def pachube(API_KEY, feed, datastream, value):
	opener = urllib2.build_opener(urllib2.HTTPHandler)
	request = urllib2.Request("http://api.pachube.com/v2/feeds/"+str(feed)+".csv", data=str(datastream)+','+str(value))
	request.add_header('X-PachubeApiKey', API_KEY)
	request.get_method = lambda: 'PUT'
	url = opener.open(request)

### BugOne ###
import rfm12
import bugOne
import sys, time

log = open("data.log", "a+")
log2 = open("messages.log", "a+")
try:
	sniffer = rfm12.SnifferSerial()
	register = [(0x16, 0, 15809, 0), (0x16, 1, 15809, 1)]
	while True:
		message = sniffer.waitForMessage()
		if message == None:
			continue
		# Log header
		t = time.gmtime()
		header = "@(%s) " % (time.strftime("%d-%m-%Y %H:%M:%S", t))
		# Save message
		log2.write(header + "[%s]%s" % (len(message), message) + '\n')
		log2.flush()
		# Handle data
		messageType = bugOne.getPacketType(message)
		srcNodeId = bugOne.getPacketSrc(message)
		destNodeId = bugOne.getPacketDest(message)
		if messageType == bugOne.PACKET_VALUES:
			values = bugOne.readValues(bugOne.getPacketData(message))
			for (srcDevice, destDevice, value) in values:
				for (rSrcNodeId, rSrcDevice, pachubeFeed, pachubeStream) in register:
					if srcNodeId == rSrcNodeId and srcDevice == rSrcDevice:
						data = header + "%s,%s=%s" % (pachubeFeed, pachubeStream, value)
						log.write(data+'\n')
						log.flush()
						pachube(PACHUBE_API_KEY, pachubeFeed, pachubeStream, value)
except Exception as e:
	print >>sys.stderr, e

log.close()
log2.close()
