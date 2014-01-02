### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=ds18b20
DEVICE_FILES=led.o ds18x20.o onewire.o crc8.o dht11.o
FILES=main.o

BASE=network.o ping.o get.o apps.o value.o config.o uart.o rfm12.o bugOne.o


include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c

# CUSTOM RULE: -std=c99
$(BOARD)/ds18x20.o: $(BUGONE_PATH)/devices/ds18x20.c $(BUGONE_PATH)/devices/ds18x20.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/ds18x20.c -o $(BOARD)/ds18x20.o

$(BOARD)/onewire.o: $(BUGONE_PATH)/devices/onewire.c $(BUGONE_PATH)/devices/onewire.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/onewire.c -o $(BOARD)/onewire.o

$(BOARD)/crc8.o: $(BUGONE_PATH)/devices/crc8.c $(BUGONE_PATH)/devices/crc8.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/crc8.c -o $(BOARD)/crc8.o

$(BOARD)/dht11.o: $(BUGONE_PATH)/devices/dht11.c $(BUGONE_PATH)/devices/dht11.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/dht11.c -o $(BOARD)/dht11.o
