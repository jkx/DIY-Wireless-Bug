
PRG=dht11

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o

$(BOARD)/dht11.o:../../devices/dht11.c
	$(CC) $(CFLAGS) -std=c99 -c ../../devices/dht11.c -o $(BOARD)/dht11.o

$(BOARD)/led.o:../../devices/led.c
	$(CC) $(CFLAGS) -c ../../devices/led.c -o $(BOARD)/led.o

$(BOARD)/const.o:../../devices/const.c
	$(CC) $(CFLAGS) -c ../../devices/const.c -o $(BOARD)/const.o

$(BOARD)/$(PRG).elf:base $(BOARD)/uart.o $(BOARD)/main.o $(BOARD)/dht11.o $(BOARD)/led.o $(BOARD)/const.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o



