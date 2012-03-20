from web.models import DeviceData
from web.models import BugNet
from web.models import BugNetNode
from web.models import BugNetDevice
from web.models import DeviceDescription

from django.contrib import admin


class BugNetAdmin(admin.ModelAdmin):
    list_display = ('name', 'location', 'contact')
    list_display_links = ('name',)
    list_editable = ('location', 'contact')


class BugNetNodeAdmin(admin.ModelAdmin):
    list_display = ('bugnet', 'location', 'node_id')


class BugNetDeviceAdmin(admin.ModelAdmin):
    list_display = ('node', 'device_description', 'device_id')


class DeviceDataAdmin(admin.ModelAdmin):
    list_display = ('timestamp', 'bugnet', 'node_id', 'device_id', 'data')
    list_filter = ('bugnet', 'node_id', 'device_id')
    date_hierarchy = 'timestamp'


class DeviceDescriptionAdmin(admin.ModelAdmin):
    list_display = ('name', )


admin.site.register(DeviceData, DeviceDataAdmin)
admin.site.register(BugNet, BugNetAdmin)
admin.site.register(BugNetNode, BugNetNodeAdmin)
admin.site.register(BugNetDevice, BugNetDeviceAdmin)
admin.site.register(DeviceDescription, DeviceDescriptionAdmin)
