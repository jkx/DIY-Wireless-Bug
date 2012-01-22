
PRG=hh10d

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o

$(BOARD)/hh10d.o:hh10d.c
	$(CC) $(CFLAGS) -c hh10d.c -o $(BOARD)/hh10d.o

$(BOARD)/twi.o:twi.c
	$(CC) $(CFLAGS) -c twi.c -o $(BOARD)/twi.o

$(BOARD)/$(PRG).elf:base $(BOARD)/main.o $(BOARD)/hh10d.o $(BOARD)/twi.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o



