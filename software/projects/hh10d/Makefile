
PRG=hh10d

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o

$(BOARD)/hh10d.o:../../devices/hh10d.c
	$(CC) $(CFLAGS) -c ../../devices/hh10d.c -o $(BOARD)/hh10d.o
$(BOARD)/twi.o:../../devices/twi.c
	$(CC) $(CFLAGS) -c ../../devices/twi.c -o $(BOARD)/twi.o

$(BOARD)/led.o:../../devices/led.c
	$(CC) $(CFLAGS) -c ../../devices/led.c -o $(BOARD)/led.o

$(BOARD)/const.o:../../devices/const.c
	$(CC) $(CFLAGS) -c ../../devices/const.c -o $(BOARD)/const.o

$(BOARD)/button.o:../../devices/button.c
	$(CC) $(CFLAGS) -c ../../devices/button.c -o $(BOARD)/button.o

$(BOARD)/$(PRG).elf:base $(BOARD)/main.o $(BOARD)/hh10d.o $(BOARD)/twi.o $(BOARD)/led.o $(BOARD)/const.o $(BOARD)/button.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o



