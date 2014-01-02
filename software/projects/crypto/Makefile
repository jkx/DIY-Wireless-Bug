### PROJECT CONFIG ###
BUGONE_PATH=../..
BOARD=bugone

PRG=test
NO_RFM12=1
FILES=main.o aes_dec.o aes_enc.o aes_keyschedule.o aes_sbox.o aes128_enc.o aes128_dec.o aes_invsbox.o gf256mul.o

include $(BUGONE_PATH)/projects/bugone.inc

$(BOARD)/main.o:main.c
$(BOARD)/aes_keyschedule.o:    $(CORE)/aes/aes_keyschedule.c
$(BOARD)/aes_sbox.o:    $(CORE)/aes/aes_sbox.c
$(BOARD)/aes128_enc.o: $(CORE)/aes/aes128_enc.c
$(BOARD)/aes128_dec.o: $(CORE)/aes/aes128_dec.c
$(BOARD)/aes_dec.o: $(CORE)/aes/aes_dec.c
$(BOARD)/aes_enc.o: $(CORE)/aes/aes_enc.c
$(BOARD)/aes_invsbox.o: $(CORE)/aes/aes_invsbox.c
$(BOARD)/gf256mul.o: $(CORE)/aes/gf256mul.S

