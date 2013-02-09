# -*- coding: utf-8 -*-

from django.conf.urls.defaults import *

urlpatterns = patterns('',
    url(r'^(?P<bugnet>\w+)/$',
        'web.views.nodes'),
    url(r'^(?P<bugnet>\w+)/(?P<node_id>\d+)/$',
        'web.views.devices'),
    url(r'^(?P<bugnet>\w+)/(?P<node_id>\d+)/(?P<device_id>\d+)/$',
        'web.views.data'),
)
