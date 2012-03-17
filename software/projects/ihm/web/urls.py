# -*- coding: utf-8 -*-

from django.conf.urls.defaults import *

urlpatterns = patterns('',
    url(r'^$',
        'web.views.index'),
    url(r'^node/(?P<node_id>\d+)/$',
        'web.views.node'),
    url(r'^(?P<bugnet>\w+)/(?P<node_id>\d+)/(?P<device_id>\d+)/$',
        'web.views.index'),
)
