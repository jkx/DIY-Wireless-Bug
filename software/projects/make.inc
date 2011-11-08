

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

CORE=../../core/

CC=avr-gcc
AS=avr-as
CPP=avr-cpp
OBJCOPY=avr-objcopy
CFLAGS=-I../../boards/$(BOARD) -I$(CORE) -I$(CORE)/uart -I$(CORE)/protocol -I$(CORE)/aes -mmcu=$(MCU) -Os



all:preconfig $(BOARD)/$(PRG).hex

readaddress:
	echo "dump eeprom 0 1" | avrdude $(DUDE_OPT) -qq -t

writeaddress:
ifndef ADDRESS
	echo "Please specify ADDRESS"
else
	echo "write eeprom 0 $(ADDRESS)" | avrdude $(DUDE_OPT) -qq -t
endif

preconfig:
	@mkdir -p $(BOARD)

clean:
	rm -rf $(BOARD)
	rm -rf *.o


load: preconfig $(BOARD)/$(PRG).hex
	avrdude $(DUDE_OPT) -U flash:w:$(BOARD)/$(PRG).hex


$(BOARD)/$(PRG.hex):$(BOARD)/$(PRG).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(BOARD)/$(PRG).elf $(BOARD)/$PRG.hex	


$(BOARD)/network.o: $(CORE)/protocol/network.c $(CORE)/protocol/network.h
	$(CC) $(CFLAGS) -c $(CORE)/protocol/network.c -o $(BOARD)/network.o	

$(BOARD)/ping.o:  $(CORE)/protocol/ping.c $(CORE)/protocol/ping.h
	$(CC) $(CFLAGS) -c $(CORE)/protocol/ping.c -o $(BOARD)/ping.o	


$(BOARD)/get.o: 
	$(CC) $(CFLAGS) -c $(CORE)/protocol/get.c -o $(BOARD)/get.o	


$(BOARD)/apps.o:
	$(CC) $(CFLAGS) -c $(CORE)/apps.c -o $(BOARD)/apps.o


$(BOARD)/value.o:
	$(CC) $(CFLAGS) -c $(CORE)/protocol/value.c -o $(BOARD)/value.o	


$(BOARD)/config.o:
	$(CC) $(CFLAGS) -c $(CORE)/config.c -o $(BOARD)/config.o	


$(BOARD)/uart.o:
	$(CC) $(CFLAGS) -c $(CORE)/uart/uart.c -o $(BOARD)/uart.o


$(BOARD)/rfm12.o:
	$(CC) $(CFLAGS) -c $(CORE)/rfm12.c -o $(BOARD)/rfm12.o

base: $(BOARD)/network.o $(BOARD)/ping.o $(BOARD)/get.o $(BOARD)/apps.o $(BOARD)/value.o $(BOARD)/config.o $(BOARD)/uart.o $(BOARD)/rfm12.o
