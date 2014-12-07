### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone_mini

PRG=sht21
DEVICE_FILES=led.o sht2x.o ds18x20.o onewire.o crc8.o twi.o bandgap.o
FILES=main.o

include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c

# CUSTOM RULE: -std=c99
$(BOARD)/sht2x.o: $(BUGONE_PATH)/devices/sht2x.c $(BUGONE_PATH)/devices/sht2x.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/sht2x.c -o $(BOARD)/sht2x.o

$(BOARD)/twi.o: $(BUGONE_PATH)/devices/twi.c $(BUGONE_PATH)/devices/twi.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/twi.c -o $(BOARD)/twi.o

$(BOARD)/ds18x20.o: $(BUGONE_PATH)/devices/ds18x20.c $(BUGONE_PATH)/devices/ds18x20.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/ds18x20.c -o $(BOARD)/ds18x20.o

$(BOARD)/onewire.o: $(BUGONE_PATH)/devices/onewire.c $(BUGONE_PATH)/devices/onewire.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/onewire.c -o $(BOARD)/onewire.o

$(BOARD)/crc8.o: $(BUGONE_PATH)/devices/crc8.c $(BUGONE_PATH)/devices/crc8.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/crc8.c -o $(BOARD)/crc8.o
