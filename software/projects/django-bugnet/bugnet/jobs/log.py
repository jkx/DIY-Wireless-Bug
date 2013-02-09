from django_extensions.management.jobs import BaseJob
from bugnet.models import BugNet
from bugnet.models import BugNetNode
from bugnet.models import BugNetDevice

import time

import bugnet.rfm12 as rfm12
import bugnet.bugOne as bugOne

from socket import socket

CARBON_SERVER = '127.0.0.1'
CARBON_PORT = 2003


class Job(BaseJob):
    help = "Log bugnet."
    sock = None

    def connect_to_graphite(self):
        sock = socket()
        try:
            sock.connect((CARBON_SERVER, CARBON_PORT))
            self.sock = sock
        except:
            print "Couldn't connect to %(server)s on port %(port)d," \
                "is carbon-agent.py running?" % \
                {'server': CARBON_SERVER, 'port': CARBON_PORT}
            return

    def send_to_graphite(self, message):
        """ Send metrics to graphite """
        if (self.sock is None):
            self.connect_to_graphite()
            if self.sock is None:
                return
        try:
            self.sock.sendall(message)
        except:
            self.sock.close()
            self.sock = None
            self.send_to_graphite(message)

    def execute(self):
        sniffer = rfm12.SnifferEthernet()

        while True:
            msg = sniffer.waitForMessage()
            if msg:
                # Extract and find bugnet
                bugnet_id = msg[0:6]
                mac_bugnet_id = ':'.join('%02x' % ord(b) for b in bugnet_id)
                bugnet = BugNet.objects.get(mac=mac_bugnet_id)
                print "Logging data of %s bugnet" % bugnet.name
                msg = msg[6:]

                # Find node
                msgType = bugOne.getPacketType(msg)
                srcNodeId = bugOne.getPacketSrc(msg)
                try:
                    srcNode = BugNetNode.objects.get(node_id=srcNodeId, bugnet=bugnet)
                    srcNodeName = srcNode.location
                except BugNetNode.DoesNotExist:
                    print "%d node not defined" % srcNodeId
                    continue
                except Exception as e:
                    print e

                # Get values of devices of this node
                if msgType == bugOne.PACKET_VALUES:
                    values = bugOne.readValues(bugOne.getPacketData(msg))

                    now = int(time.time())
                    lines = []

                    for (srcDevice, dstDevice, data) in values:
                        try:
                            srcDevice = BugNetDevice.objects.get(device_id=srcDevice, node=srcNode)
                            srcDeviceName = srcDevice.device_description
                            lines.append("%s.%s.%s %s %d" %
                                (bugnet.name, srcNodeName, srcDevice, data, now))
                        except BugNetDevice.DoesNotExist:
                            print "%d device not defined" % srcDevice
                        except Exception as e:
                            print e

                    message = '\n'.join(lines) + '\n'
                    print message
                    self.send_to_graphite(message)
