MCU=atmega168
CC=avr-gcc
OBJCOPY=avr-objcopy


CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues -I../include
#CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -mcall-prologues



all: main.hex

help: 
	@echo "Usage avrprg: make help|all|load|load_pre|loadavrdude|loadavrdude_pre"
	@echo "Usage prgfuses: make help|rdfuses|wrfuses"


main.hex : main.out
	$(OBJCOPY) -R .eeprom -O ihex main.out main.hex -g
main.out :  main.o
	$(CC) $(CFLAGS) -o  main.out -Wl,-Map,main.map main.o -lm
	avr-size main.out

main.o : main.c main.h
	$(CC) $(CFLAGS) -c main.c


check:	
	@echo "Loading kernel modules ...."
	@echo ""
	@/sbin/modprobe parport
	@/sbin/modprobe parport_pc
	@/sbin/modprobe ppdev
	@uisp -dlpt=/dev/parport0 -dprog=ett
	@echo ""


clean:
	rm -f *.o *.map *.out *.hex *~


#wrfuses:
#	uisp 
#sudo avarice -g -j usb -W E499E4


rdfuses:
	uisp -dlpt=/dev/parport0 -dprog=dapa --rd_fuses

wrfuses:
#	uisp -dlpt=/dev/parport0 -dprog=dapa --wr_fuse_l=0x64 --wr_fuse_h=0xDF
#	avrdude -p m8 -c dapa -U lfuse:w:0xa4:m -U hfuse:w:0xd9:m 
	avrdude -p atmega168 -c stk500v2 -P /dev/ttyUSB0 -b 115200 -U lfuse:w:0xE2:m -U hfuse:w:0xdf:m -U efuse:w:0x02:m


ddd: gdbinit
	ddd --debugger "avr-gdb -x gdb.conf"

gdbserver: gdbinit
	sudo avarice -g -j usb --erase --program --file main.hex :4242

gdbinit: main.hex
	@echo "file main.out" > gdb.conf
	@echo "target remote localhost:4242"    >> gdb.conf
	@echo
#@echo "Use 'avr-gdb -x gdb.conf'"

run: main.hex
	sudo ls
	sudo avarice -B 2000000  -g -j usb --erase --program --file main.hex :4242 &
	sleep 2;
	ddd --debugger "avr-gdb -x gdb.conf"

#@echo "load"        >> gdb.conf	
#@echo "break main"  >> gdb.conf
#@echo "continue"    >> gdb.conf



#--------------
# load (program) the software into the eeprom:
load: main.hex
	avrdude -p atmega168 -c stk500v2 -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex -y -V	

