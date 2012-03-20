# Create your views here.

from django.http import HttpResponse
from django.core import serializers

from django.shortcuts import get_list_or_404
from django.shortcuts import render_to_response

from web.models import DeviceData
from web.models import BugNet
from web.models import BugNetNode
from web.models import BugNetDevice


def data(request, bugnet, node_id, device_id):
    datas = DeviceData.objects.filter(bugnet=BugNet.objects.filter(name=bugnet),node_id=node_id,device_id=device_id).order_by('timestamp').reverse()[:100]
    return render_to_response("data.json", {'bugnet' : 'kerellou', 'datas':
        datas}, mimetype = 'application/javascript')


def devices(request, bugnet, node_id):
    devices = BugNetDevice.objects.filter(
                node=BugNetNode.objects.filter(node_id=node_id,bugnet=BugNet.objects.filter(name=bugnet)))
    return render_to_response("devices.html", {'devices' : devices})


def nodes(request, bugnet):
    nodes = BugNetNode.objects.filter(
                bugnet=BugNet.objects.filter(name=bugnet))
    return render_to_response("bugnet.html",
            {'bugnet' : bugnet, 'nodes' : nodes})
