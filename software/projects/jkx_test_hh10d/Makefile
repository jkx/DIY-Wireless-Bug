
PRG=test

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o -Wl,-u,vfprintf -lprintf_flt 


$(BOARD)/$(PRG).elf:$(BOARD)/uart.o $(BOARD)/main.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o -Wl,-u,vfprintf -lprintf_flt 



