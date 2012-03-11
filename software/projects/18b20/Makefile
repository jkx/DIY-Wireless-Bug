
PRG=ds18x20

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o

$(BOARD)/ds18x20.o:../../devices/ds18x20.c
	$(CC) $(CFLAGS) -DF_CPU=8000000 -c ../../devices/ds18x20.c -o $(BOARD)/ds18x20.o

$(BOARD)/onewire.o:../../devices/onewire.c
	$(CC) $(CFLAGS) -std=c99 -DF_CPU=8000000 -c ../../devices/onewire.c -o $(BOARD)/onewire.o

$(BOARD)/crc8.o:../../devices/crc8.c
	$(CC) $(CFLAGS) -c ../../devices/crc8.c -o $(BOARD)/crc8.o

$(BOARD)/led.o:../../devices/led.c
	$(CC) $(CFLAGS) -c ../../devices/led.c -o $(BOARD)/led.o

$(BOARD)/const.o:../../devices/const.c
	$(CC) $(CFLAGS) -c ../../devices/const.c -o $(BOARD)/const.o

$(BOARD)/enc28j60.o:enc28j60.c
	$(CC) $(CFLAGS) -c enc28j60.c -o $(BOARD)/enc28j60.o

$(BOARD)/ip_arp_udp_tcp.o:ip_arp_udp_tcp.c
	$(CC) $(CFLAGS) -c ip_arp_udp_tcp.c -o $(BOARD)/ip_arp_udp_tcp.o

$(BOARD)/$(PRG).elf:base $(BOARD)/main.o $(BOARD)/ds18x20.o $(BOARD)/onewire.o $(BOARD)/crc8.o $(BOARD)/enc28j60.o $(BOARD)/ip_arp_udp_tcp.o $(BOARD)/led.o $(BOARD)/const.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o



