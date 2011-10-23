$CC $CFLAGS -c ../../core/uart/uart.c -o $BOARD/uart.o
$CC $CFLAGS -c ../../core/rfm12.c -o $BOARD/rfm12.o
$CC $CFLAGS -c ../../core/config.c -o $BOARD/config.o
$CC $CFLAGS -c ../../core/protocol/value.c -o $BOARD/value.o
$CC $CFLAGS -c ../../core/protocol/network.c -o $BOARD/network.o
$CC $CFLAGS -c ../../core/protocol/ping.c -o $BOARD/ping.o
$CC $CFLAGS -c lm35.c -o $BOARD/lm35.o
$CC $CFLAGS -c main.c -o $BOARD/main.o
