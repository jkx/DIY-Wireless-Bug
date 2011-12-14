PRG=sniffer

include ../make.inc

$(BOARD)/sniffer.o: sniffer.c
	$(CC) $(CFLAGS) -c sniffer.c -o $(BOARD)/sniffer.o

$(BOARD)/$(PRG).elf:$(BOARD)/uart.o $(BOARD)/rfm12.o $(BOARD)/sniffer.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o

