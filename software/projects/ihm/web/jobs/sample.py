from django_extensions.management.jobs import BaseJob
from web.models import DeviceData
from web.models import BugNet

import random
import datetime

class Job(BaseJob):
    help = "My sample job."

    def execute(self):
        print "Fill device data table with sample data"
        t = datetime.datetime.today()
        td = datetime.timedelta(minutes=1)
        for i in range(100):
            d = DeviceData(node_id=1,device_id=1)
            t = t + td
            print t
            d.timestamp = t
            d.data = random.randint(0,100)
            d.bugnet = BugNet.objects.get(name='kerellou')
            d.save()
