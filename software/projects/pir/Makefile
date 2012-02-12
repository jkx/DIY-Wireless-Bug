
PRG=pir

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o

$(BOARD)/lm35.o:lm35.c
	$(CC) $(CFLAGS) -c lm35.c -o $(BOARD)/lm35.o

$(BOARD)/$(PRG).elf:base $(BOARD)/main.o $(BOARD)/lm35.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o



