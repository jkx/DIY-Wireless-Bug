
PRG=ds18x20

include ../make.inc




$(BOARD)/main.o:main.c
	$(CC) $(CFLAGS) -c main.c -o $(BOARD)/main.o

$(BOARD)/ds18x20.o:ds18x20.c
	$(CC) $(CFLAGS) -DF_CPU=8000000 -c ds18x20.c -o $(BOARD)/ds18x20.o

$(BOARD)/onewire.o:onewire.c
	$(CC) $(CFLAGS) -std=c99 -DF_CPU=8000000 -c onewire.c -o $(BOARD)/onewire.o

$(BOARD)/crc8.o:crc8.c
	$(CC) $(CFLAGS) -c crc8.c -o $(BOARD)/crc8.o

$(BOARD)/enc28j60.o:enc28j60.c
	$(CC) $(CFLAGS) -c enc28j60.c -o $(BOARD)/enc28j60.o

$(BOARD)/ip_arp_udp_tcp.o:ip_arp_udp_tcp.c
	$(CC) $(CFLAGS) -c ip_arp_udp_tcp.c -o $(BOARD)/ip_arp_udp_tcp.o

$(BOARD)/$(PRG).elf:base $(BOARD)/main.o $(BOARD)/ds18x20.o $(BOARD)/onewire.o $(BOARD)/crc8.o $(BOARD)/enc28j60.o $(BOARD)/ip_arp_udp_tcp.o
	$(CC) $(CFLAGS) -o $(BOARD)/$(PRG).elf $(BOARD)/*.o



