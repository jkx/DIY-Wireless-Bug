from django_extensions.management.jobs import BaseJob
from web.models import DeviceData
from web.models import BugNet
from web.models import BugNetNode
from web.models import BugNetDevice

import random
import datetime
import time
import sys

sys.path.append("/home/a2683/rfm12/DIY-Wireless-Bug/software/projects/sniffer/Python/")

import rfm12
import bugOne

from socket import socket

CARBON_SERVER = '127.0.0.1'
CARBON_PORT = 2003

class Job(BaseJob):
    help = "Log bugnet."

    def execute(self):
        bugnet_name = 'kerellou'
        device = "/dev/ttyUSB0"

        bugnet = BugNet.objects.get(name=bugnet_name)
        print "Logging data of %s bugnet" % bugnet_name

        sock = socket()
        try:
            sock.connect((CARBON_SERVER,CARBON_PORT))
        except:
            print "Couldn't connect to %(server)s on port %(port)d, is carbon-agent.py running?" % { 'server':CARBON_SERVER, 'port':CARBON_PORT }
            sys.exit(1)

        sniffer = rfm12.SnifferSerial(device)

        while True:
            msg = sniffer.waitForMessage()
            if msg:
                print "#"
                msgType = bugOne.getPacketType(msg)
                srcNodeId = bugOne.getPacketSrc(msg)
		try:
                	srcNode = BugNetNode.objects.get(node_id=srcNodeId)
                	srcNodeName = srcNode.location
		except BugNetNode.DoesNotExist:
			print "%d device not defined" % srcNodeId
		except Exception as e:
			print e
			

                if msgType == bugOne.PACKET_VALUES:
                    print "@"
                    values = bugOne.readValues(bugOne.getPacketData(msg))
                    print values

                    now = int(time.time())
                    lines = []
                    #lines.append("%s.%s.%s %s %d" % (bugnet_name,srcNodeId,srcDevice,values,now))

                    for (srcDevice,dstDevice,value) in values:
                        srcDevice = BugNetDevice.objects.get(device_id=srcDevice)
                        srcDeviceName = srcDevice.device_description
                        lines.append("%s.%s.%s %s %d" %
                                (bugnet_name,srcNodeName,srcDevice,value,now))

                    message = '\n'.join(lines) + '\n'
                    print message
                    sock.sendall(message)
