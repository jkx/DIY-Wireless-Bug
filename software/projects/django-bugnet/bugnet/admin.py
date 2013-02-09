from bugnet.models import BugNet
from bugnet.models import BugNetNode
from bugnet.models import BugNetDevice
from bugnet.models import DeviceDescription

from django.contrib import admin


class BugNetAdmin(admin.ModelAdmin):
    list_display = ('name', 'location', 'contact','mac')
    list_display_links = ('name',)
    list_editable = ('location', 'contact','mac')


class BugNetDeviceAdmin(admin.ModelAdmin):
    list_display = ('node', 'device_description', 'device_id')


class BugNetDeviceInline(admin.TabularInline):
    model = BugNetDevice


class BugNetNodeAdmin(admin.ModelAdmin):
    list_display = ('bugnet', 'location', 'node_id')
    inlines = [ BugNetDeviceInline ]


class DeviceDescriptionAdmin(admin.ModelAdmin):
    list_display = ('name', )


admin.site.register(BugNet, BugNetAdmin)
admin.site.register(BugNetNode, BugNetNodeAdmin)
admin.site.register(BugNetDevice, BugNetDeviceAdmin)
admin.site.register(DeviceDescription, DeviceDescriptionAdmin)
