PRG=sniffer

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o


$(BOARD)/$(PRG).hex:$(BOARD)/network.o $(BOARD)/ping.o $(BOARD)/get.o $(BOARD)/apps.o $(BOARD)/value.o $(BOARD)/config.o $(BOARD)/uart.o $(BOARD)/rfm12.o $(BOARD)/main.o

	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o
	avr-size $(BOARD)/$(PRG).elf



