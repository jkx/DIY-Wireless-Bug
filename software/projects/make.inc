

# defaut 
BOARD=bugone
PORT=/dev/ttyUSB0



ifeq ($(BOARD),bugone)
	MCU=atmega168
	DUDE_OPT =-c usbasp -p m168
endif


ifeq ($(BOARD),arduino)
	MCU=atmega328p
	DUDE_OPT=-c arduino -p m328p -P$(PORT) -b57600
endif


ifeq ($(BOARD),veroboard)
	MCU=atmega88
	DUDE_OPT=-c avrisp -p m88 -P$(PORT) -b19200
endif



CC=avr-gcc
AS=avr-as
CPP=avr-cpp
OBJCOPY=avr-objcopy
CFLAGS=-I../../boards/$(BOARD) -I../../core -I../../core/uart -I../../core/protocol -I../../core/aes -mmcu=$(MCU) -Os


all:preconfig $(BOARD)/$(PRG).hex

preconfig:
	@mkdir -p $(BOARD)

clean:
	rm -rf $(BOARD)
	rm -rf *.o


load: preconfig $(BOARD)/$(PRG).hex
	avrdude $(DUDE_OPT) -U flash:w:$(BOARD)/$(PRG).hex


$(BOARD)/$(PRG.hex):$(BOARD)/$(PRG).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(BOARD)/$(PRG).elf $(BOARD)/$PRG.hex	


$(BOARD)/network.o: ../../core/protocol/network.c ../../core/protocol/network.h
	$(CC) $(CFLAGS) -c ../../core/protocol/network.c -o $(BOARD)/network.o	

$(BOARD)/ping.o:  ../../core/protocol/ping.c ../../core/protocol/ping.h
	$(CC) $(CFLAGS) -c ../../core/protocol/ping.c -o $(BOARD)/ping.o	


$(BOARD)/get.o: 
	$(CC) $(CFLAGS) -c ../../core/protocol/get.c -o $(BOARD)/get.o	


$(BOARD)/apps.o:
	$(CC) $(CFLAGS) -c ../../core/apps.c -o $(BOARD)/apps.o


$(BOARD)/value.o:
	$(CC) $(CFLAGS) -c ../../core/protocol/value.c -o $(BOARD)/value.o	


$(BOARD)/config.o:
	$(CC) $(CFLAGS) -c ../../core/config.c -o $(BOARD)/config.o	


$(BOARD)/uart.o:
	$(CC) $(CFLAGS) -c ../../core/uart/uart.c -o $(BOARD)/uart.o


$(BOARD)/rfm12.o:
	$(CC) $(CFLAGS) -c ../../core/rfm12.c -o $(BOARD)/rfm12.o
