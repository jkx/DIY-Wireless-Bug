### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=ds18b20
DEVICE_FILES=const.o led.o ds18x20.o onewire.o crc8.o
FILES=main.o

include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c

# CUSTOM RULE: -std=c99
$(BOARD)/ds18x20.o: $(BUGONE_PATH)/devices/ds18x20.c $(BUGONE_PATH)/devices/ds18x20.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/ds18x20.c -o $(BOARD)/ds18x20.o

$(BOARD)/onewire.o: $(BUGONE_PATH)/devices/onewire.c $(BUGONE_PATH)/devices/onewire.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/onewire.c -o $(BOARD)/onewire.o

$(BOARD)/crc8.o: $(BUGONE_PATH)/devices/crc8.c $(BUGONE_PATH)/devices/crc8.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/crc8.c -o $(BOARD)/crc8.o

