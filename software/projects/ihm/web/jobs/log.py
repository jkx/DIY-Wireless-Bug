from django_extensions.management.jobs import BaseJob
from web.models import DeviceData
from web.models import BugNet

import random
import datetime
import sys

sys.path.append("/home/a2683/rfm12/DIY-Wireless-Bug/software/projects/raw_sniffer/")

import rfm12
import bugOne

class Job(BaseJob):
    help = "Log bugnet."

    def execute(self):
        bugnet_name = 'kerellou'
        device = "/dev/ttyUSB0"

        bugnet = BugNet.objects.get(name=bugnet_name)
        print "Logging data of %s bugnet" % bugnet_name

        sniffer = rfm12.SnifferSerial(device)

        while True:
            msg = sniffer.waitForMessage()
            if msg:
                print "#"
                msgType = bugOne.getPacketType(msg)
                srcNodeId = bugOne.getPacketSrc(msg)

                if msgType == bugOne.PACKET_VALUES:
                    print "@"
                    values = bugOne.readValues(bugOne.getPacketData(msg))
                    print values

                    for (srcDevice,dstDevice,value) in values:
                        d = DeviceData()
                        d.timestamp = datetime.datetime.today()
                        d.bugnet = bugnet
                        d.node_id = srcNodeId
                        d.device_id = srcDevice
                        d.data = value
                        d.save()

                        print d

            else:
                print "."
