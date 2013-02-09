from django.db import models
from macaddress.fields import MACAddressField


class BugNet(models.Model):
    name = models.CharField(max_length=64)
    location = models.CharField(max_length=64, blank=True)
    contact = models.EmailField()
    mac = MACAddressField(blank=True)

    def __unicode__(self):
        return self.name


class BugNetNode(models.Model):
    bugnet = models.ForeignKey(BugNet)
    location = models.CharField(max_length=64)
    node_id = models.IntegerField()

    def __unicode__(self):
        return "%s, %s" % (self.bugnet.name, self.location)


class DeviceDescription(models.Model):
    name = models.CharField(max_length=32)

    def __unicode__(self):
        return self.name


class BugNetDevice(models.Model):
    node = models.ForeignKey(BugNetNode)
    device_description = models.ForeignKey(DeviceDescription)
    device_id = models.IntegerField()

    def __unicode__(self):
        return self.device_description.name
