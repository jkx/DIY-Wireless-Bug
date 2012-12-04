### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=enc28j60
DEVICE_FILES=const.o led.o
FILES=main.o enc28j60.o ip_arp_udp_tcp.o dhcp_client.o dnslkup.o config.o
BASE=network.o ping.o get.o apps.o value.o uart.o rfm12.o bugOne.o

include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c

$(BOARD)/enc28j60.o:enc28j60.c
	$(CC) $(CFLAGS) -c enc28j60.c -o $(BOARD)/enc28j60.o

$(BOARD)/timeout.o:timeout.c
	$(CC) $(CFLAGS) -c timeout.c -o $(BOARD)/timeout.o

$(BOARD)/ip_arp_udp_tcp.o:ip_arp_udp_tcp.c
	$(CC) $(CFLAGS) -c ip_arp_udp_tcp.c -o $(BOARD)/ip_arp_udp_tcp.o

$(BOARD)/dhcp_client.o:dhcp_client.c
	$(CC) $(CFLAGS) -c dhcp_client.c -o $(BOARD)/dhcp_client.o

$(BOARD)/dnslkup.o:dnslkup.c
	$(CC) $(CFLAGS) -c dnslkup.c -o $(BOARD)/dnslkup.o
