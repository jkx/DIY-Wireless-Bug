#!/usr/bin/python
#-*- coding: utf-8 -*-

import sys
import time

import rfm12
import bugOne

# 
# Send a ping, wait for a pong
#
def test_ping(sniffer, nodeid):
	print "ping"

	bugOne.ping(nodeid, sniffer)
	message = sniffer.waitForMessage()

	if message and bugOne.getPacketType(message) == bugOne.PACKET_PONG:
		return True
	return False

#
# Turn on led 1 on tested bugone
#
def test_set_led1(sniffer, nodeid):
	print "Turn on led 1"
	bugOne.setValue(nodeid, 0, 1, value=1, sniffer=sniffer)

	while True:
		answer = raw_input("led1 in on ? (y/n) ")

		if (answer.lower() == 'y'):
			return True
		elif (answer.lower() == 'n'):
			return False

#
# Turn off led 1 on tested bugone
#
def test_clr_led1(sniffer, nodeid):
	print "Turn off led 1"
	bugOne.setValue(nodeid, 0, 1, value=0, sniffer=sniffer)

	while True:
		answer = raw_input("led1 in off ? (y/n) ")

		if (answer.lower() == 'y'):
			return True
		elif (answer.lower() == 'n'):
			return False

#
# Get value of the 1st device, should be 42 (const device)
#
def test_get_const(sniffer, nodeid):
	print "Get value device 1"
	value = bugOne.getValue(nodeid, 0, 0, sniffer)
	print "value is %s" % value

	if value == 42:
		return True
	return False

#
# Get state of the led
#
def test_get_led1(sniffer, nodeid):
	print "Get state led 1"
	value = bugOne.getValue(nodeid, 0, 1, sniffer)
	print "state is %s" % value

	if value == 1:
		return True
	return False

#
# Get state of an undeclared device
#
def test_get_unknown_device(sniffer, nodeid):
    print "Get state of unknown device"
    return False

print """
bugOne test suite.
==================

"""

if len(sys.argv) != 2:
	print >>sys.stderr, "usage:", sys.argv[0], "<node id (int)>"
	exit(1)

sniffer = rfm12.SnifferSerial()
destNodeId = int(sys.argv[1])

print "Running testsuite with node %s" % destNodeId

tests = [ test_ping, test_get_const, test_set_led1, test_get_led1, test_clr_led1 ]
nb_tests_ok=0
nb_tests_ko=0

for test in tests:
	print "***" ,
	if test(sniffer,destNodeId):
		nb_tests_ok+=1
		print "===> OK"
	else:
		nb_tests_ko+=1
		print "===> KO"

	time.sleep(1)

print """

testsuite summary
=================
total number of test : %s
number of OK         : %s
number of KO         : %s""" % (len(tests),nb_tests_ok,nb_tests_ko)
