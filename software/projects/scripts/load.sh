PRG=hello

if [ $# -ne 1 ]; then
	echo "Error: Specify target board (arduino, veroboard, bugone)"
	exit 1
fi

BOARD=$1
OPTS_arduino="-c arduino -p m328p -P/dev/ttyUSB0 -b57600"
OPTS_veroboard="-c avrisp -p m88 -P/dev/ttyUSB1 -b19200"
OPTS_bugone="-c avrisp -p m168 -P/dev/ttyUSB0 -b19200"

eval OPTS=\$OPTS_$BOARD

cd $BOARD

set -x
avrdude $OPTS -U flash:w:$PRG.hex
