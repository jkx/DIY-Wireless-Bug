# Create your views here.

from django.http import HttpResponse
from django.core import serializers

from django.shortcuts import get_list_or_404
from django.shortcuts import render_to_response

from web.models import DeviceData
from web.models import BugNet


def index(request, bugnet, node_id, device_id):
    #if request.is_ajax():
    #    if format == 'xml':
    #        mimetype = 'application/xml'
    #    if format == 'json':
    #        mimetype = 'application/javascript'
    #    format = 'json'
    #    mimetype = 'application/javascript'
    #    data = serializers.serialize(format,
    #        DeviceData.objects.filter(bugnet=BugNet.objects.filter(name=bugnet)),
    #        fields=('timestamp','data'))
    #    return HttpResponse(data, mimetype)
    # If you want to prevent non XHR calls
    #else:
    #    return HttpResponse(status=400)

    datas = DeviceData.objects.filter(bugnet=BugNet.objects.filter(name=bugnet))
    return render_to_response("data.html", {'bugnet' : 'kerellou', 'datas':
        datas}, mimetype = 'application/javascript')


def node(request, node_id):
    response = "Node %s" % node_id
    return HttpResponse(response)
