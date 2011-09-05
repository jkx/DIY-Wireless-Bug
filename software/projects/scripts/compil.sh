#!/bin/sh

PRG=$(basename $(pwd))

if [ $# -ne 1 ]; then
	echo "Error: Specify target board (arduino, veroboard, bugone)"
	exit 1
fi

MCU_arduino=atmega328p
MCU_veroboard=atmega88
MCU_bugone=atmega168

BOARD=$1
eval MCU=\$MCU_$BOARD

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS="-I../../boards/$BOARD -I../../core -I../../core/uart -I../../core/protocol -mmcu=$MCU -Os"

mkdir -p $BOARD

echo "===== Compiling $PRG for $BOARD"

set -x

. ./prg_compil.sh

cd $BOARD
$CC $CFLAGS -o $PRG.elf *.o

$OBJCOPY -j .text -j .data -O ihex $PRG.elf $PRG.hex
