$CC $CFLAGS -c ../../core/uart/uart.c -o $BOARD/uart.o
$CC $CFLAGS -c ../../core/config.c -o $BOARD/config.o
$CC $CFLAGS -c ../../core/aes/aes_keyschedule.c -o $BOARD/aes_keyschedule.o
$CC $CFLAGS -c ../../core/aes/aes_sbox.c -o $BOARD/aes_sbox.o
$CC $CFLAGS -c ../../core/aes/aes128_enc.c -o $BOARD/aes128_enc.o
$CC $CFLAGS -c ../../core/aes/aes128_dec.c -o $BOARD/aes128_dec.o
$CC $CFLAGS -c ../../core/aes/aes_dec.c -o $BOARD/aes_dec.o
$CC $CFLAGS -c ../../core/aes/aes_enc.c -o $BOARD/aes_enc.o
$CC $CFLAGS -c ../../core/aes/aes_invsbox.c -o $BOARD/aes_invsbox.o
$CPP $CFLAGS ../../core/aes/gf256mul.S | $AS -o $BOARD/gf256mul.o
$CC $CFLAGS -c main.c -o $BOARD/main.o
