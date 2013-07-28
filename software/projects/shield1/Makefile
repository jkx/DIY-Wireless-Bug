### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=shield1
DEVICE_FILES=const.o led.o dht11.o photoresistor.o bandgap.o
FILES=main.o

include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c

# CUSTOM RULE: -std=c99
$(BOARD)/dht11.o: $(BUGONE_PATH)/devices/dht11.c $(BUGONE_PATH)/devices/dht11.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/dht11.c -o $(BOARD)/dht11.o

$(BOARD)/photoresistor.o: $(BUGONE_PATH)/devices/photoresistor.c $(BUGONE_PATH)/devices/photoresistor.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/photoresistor.c -o $(BOARD)/photoresistor.o

