### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=optiboot
DEVICE_FILES=
BASE=optiboot.o

include $(BUGONE_PATH)/projects/bugone.inc

CFLAGS += -DLED_START_FLASHES=3 -DLED_DATA_FLASH -DBAUD_RATE=38400 -fno-inline-small-functions -fno-split-wide-types -mshort-calls
LDFLAGS += -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe -Wl,--relax -Wl,--gc-sections -nostartfiles -nostdlib

$(BOARD)/optiboot.o:optiboot.c


bootfuses:
	avrdude $(DUDE_OPT) -U efuse:w:0x04:m
