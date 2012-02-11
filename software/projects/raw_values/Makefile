PRG=values

include ../make.inc

$(BOARD)/values.o: values.c
	$(CC) $(CFLAGS) -c values.c -o $(BOARD)/values.o

$(BOARD)/$(PRG).elf:$(BOARD)/rfm12.o $(BOARD)/values.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o

