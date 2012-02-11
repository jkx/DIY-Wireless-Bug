#!/usr/bin/python
#-*- coding: utf-8 -*-

if __name__ != "__main__":
	exit(1)

import os

pid = os.fork()
if pid != 0:
	print "Started with pid: %s" % pid
	exit(0)

### PACHUBE ###
import urllib2
def pachube(API_KEY, feed, streamValues):
	opener = urllib2.build_opener(urllib2.HTTPHandler)
	data = None
	for (stream, value) in streamValues:
		if data: data += '\n'
		else: data = ""
		data += "%s,%s" % (str(stream), str(value))
	request = urllib2.Request("http://api.pachube.com/v2/feeds/"+str(feed)+".csv", data=data)
	request.add_header('X-PachubeApiKey', API_KEY)
	request.get_method = lambda: 'PUT'
	url = opener.open(request)

### BugOne ###
import rfm12
import sys, time

pachubeFeed = 15809
PACHUBE_API_KEY="FILL ME WITH YOUR API"

log = open("data.log", "a+")
log2 = open("messages.log", "a+")
try:
	sniffer = rfm12.Sniffer()
	while True:
		try:
			message = sniffer.waitForMessage()
			if message == None:
				continue
			# Log header
			t = time.gmtime()
			header = "@(%s) " % (time.strftime("%d-%m-%Y %H:%M:%S", t))
			# Save message
			log2.write(header + "[%s]%s" % (len(message), message) + '\n')
			log2.flush()

			lightValue = rfm12.readInteger(message[0:2], bigEndian=True)
			tempValue = rfm12.readInteger(message[2:4], bigEndian=True)

			light = 100.0 - (100.0 * lightValue / 1024.0)
			temperature = (tempValue*3.3 / 1024)*10.0

			data = header + "light=%s [%s], temp=%s [%s]" % (light, lightValue, temperature, tempValue)
			log.write(data+'\n')
			log.flush()
			pachube(PACHUBE_API_KEY, pachubeFeed, [(1, light), (0, temperature)])
		except Exception as e:
			print >>sys.stderr, e
			log.write("Exception: %s\n" % str(e))
except Exception as e:
	print >>sys.stderr, e
	log.write("Exception: %s\n" % str(e))

log.close()
log2.close()
