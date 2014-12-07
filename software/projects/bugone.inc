### GLOBAL CONFIG ###

# Variable: BUGONE_PATH (REQUIRED)
# Where can we find required core/device files, should point to folder "software"

# Variable: BOARD (REQUIRED)
# Target board (supported: bugone, arduino, veroboard)
# Defines MCU, DUDE_OPTS, require a folder with adequate includes in boards dir

# Variable: PORT (Default: /dev/ttyUSB0)
# AVRDUDE programmer port
ifndef PORT
	PORT=/dev/ttyUSB0
endif



### DEFAULT BOARD CONFIGS ###

ifeq ($(BOARD),bugone)
	MCU=atmega168
	DUDE_OPT =-c avrusb500 -P$(PORT) -p m168 -V
endif

ifeq ($(BOARD),bugone_mini)
	MCU=atmega328p
	DUDE_OPT =-c avrusb500 -P$(PORT) -p m328p -V -v
endif

ifeq ($(BOARD),arduino)
	MCU=atmega328p
	DUDE_OPT=-c arduino -p m328p -P$(PORT) -V
endif

ifeq ($(BOARD),veroboard)
	MCU=atmega88
	DUDE_OPT=-c avrisp -p m88 -P$(PORT) -b19200
endif



### DEFAULT RULE ###
all: $(BOARD) $(BOARD)/$(PRG).hex



### CONSTANTS ###
CORE=$(BUGONE_PATH)/core
ifndef BASE
	_BASE=network.o ping.o get.o apps.o value.o config.o uart.o rfm12.o bugOne.o
	ifeq ($(DISABLE_MAIN), 1)
		BASE=$(_BASE)
	else
		BASE=$(_BASE) bugone_main.o
	endif
endif

ifndef DEVICE_FILES
	DEVICE_FILES=
endif

ifndef FILES
	FILES=
endif

# enable floating point printf or not ?
#CC=avr-gcc -Wl,-u,vfprintf -lprintf_flt
CC=avr-gcc -std=gnu99 -Wno-implicit-function-declaration
AS=avr-as
CPP=avr-cpp
OBJCOPY=avr-objcopy
CFLAGS=-I. -I$(BUGONE_PATH)/boards/$(BOARD) -I$(BUGONE_PATH)/devices -I$(CORE) -I$(CORE)/uart -I$(CORE)/protocol -I$(CORE)/aes -mmcu=$(MCU) -Os -DPRG=\"$(PRG)\"
LDFLAGS=-mmcu=$(MCU)


# if DISABLE_CORE is set we only use the $FILES arguments
ifeq ($(DISABLE_CORE), 1)
	OBJS=$(addprefix $(BOARD)/, uart.o $(FILES))
else
	OBJS=$(addprefix $(BOARD)/, $(BASE) $(DEVICE_FILES) $(FILES))
endif



### RULES (COMPILE) ###

$(BOARD):
	@mkdir -p $(BOARD)

clean:
	rm -rf $(BOARD)

$(BOARD)/%.o:
	@echo -- $@ --
	@$(CC) $(CFLAGS) -c $< -o $@

$(BOARD)/$(PRG).hex: $(BOARD)/$(PRG).elf
	@echo -- $@ --
	@$(OBJCOPY) -j .text -j .data -O ihex $(BOARD)/$(PRG).elf $(BOARD)/$(PRG).hex
	@avr-size $(BOARD)/$(PRG).elf

$(BOARD)/$(PRG).elf: $(BOARD) $(OBJS)
	@echo -- $@ --
	@$(CC) $(LDFLAGS) -o $(BOARD)/$(PRG).elf $(OBJS)



### RULES (PROGRAM BOARD) ###

reset:
	avrdude $(DUDE_OPT)

load: $(BOARD)/$(PRG).hex
	avrdude $(DUDE_OPT) -U flash:w:$(BOARD)/$(PRG).hex


sload: $(BOARD)/$(PRG).hex
	avrdude -c arduino -P$(PORT) -p m168 -b 38400 -U flash:w:$(BOARD)/$(PRG).hex



### RULES (DEVICE ID) ###

readaddress:
	echo "dump eeprom 0 1" | avrdude $(DUDE_OPT) -qq -t

writeaddress:
ifndef ADDRESS
	echo "Please specify ADDRESS=<decimal value>"
else
	echo "write eeprom 0 $(ADDRESS)" | avrdude $(DUDE_OPT) -qq -t
endif



### RULES (FUSES) ###

rdfuses:
	echo "dump lfuse\ndump hfuse\ndump efuse" | avrdude $(DUDE_OPT) -qq -t

wrfuses:
	# d7 = no watchdog
	# avrdude $(DUDE_OPT) -U lfuse:w:0xe2:m -U hfuse:w:0xd7:m
	avrdude $(DUDE_OPT) -U lfuse:w:0xe2:m -U hfuse:w:0xd7:m -U efuse:w:0xff:m
	#avrdude $(DUDE_OPT) -U lfuse:w:0xe2:m -U hfuse:w:0xc7:m

optifuses:
	# 0x04 = bootloader
	avrdude $(DUDE_OPT) -U lfuse:w:0xe2:m -U hfuse:w:0xd7:m -U efuse:w:0x04:m


### DEPENDENCIES ###

$(BOARD)/apps.o:    $(CORE)/apps.c $(CORE)/apps.h
$(BOARD)/bugOne.o:  $(CORE)/bugOne.c $(CORE)/bugOne.h
$(BOARD)/config.o:  $(CORE)/config.c $(CORE)/config.h
$(BOARD)/rfm12.o:   $(CORE)/rfm12.c $(CORE)/rfm12.h
$(BOARD)/uart.o:    $(CORE)/uart/uart.c $(CORE)/uart/uart.h
$(BOARD)/get.o:     $(CORE)/protocol/get.c
$(BOARD)/network.o: $(CORE)/protocol/network.c $(CORE)/protocol/network.h
$(BOARD)/ping.o:    $(CORE)/protocol/ping.c $(CORE)/protocol/ping.h
$(BOARD)/value.o:   $(CORE)/protocol/value.c $(CORE)/protocol/value.h
$(BOARD)/bugone_main.o:   $(CORE)/bugone_main.c

$(addprefix $(BOARD)/,$(DEVICE_FILES)): $(BOARD)/%.o: $(BUGONE_PATH)/devices/%.c $(BUGONE_PATH)/devices/%.h
