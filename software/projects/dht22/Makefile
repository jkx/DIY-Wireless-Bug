### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=dht22
DEVICE_FILES=const.o led.o dht22.o
FILES=main.o

include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c

# CUSTOM RULE: -std=c99
$(BOARD)/dht22.o: $(BUGONE_PATH)/devices/dht22.c $(BUGONE_PATH)/devices/dht22.h
	$(CC) $(CFLAGS) -std=c99 -c $< -o $@

$(BOARD)/lm35.o: $(BUGONE_PATH)/devices/lm35.c $(BUGONE_PATH)/devices/lm35.h
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/lm35.c -o $(BOARD)/lm35.o

