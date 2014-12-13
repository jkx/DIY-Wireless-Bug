#ifndef _TELEINFO_H_
#define _TELEINFO_H_

#include "rfm12.h"
#if RFM12_UART_DEBUG
#error "sniffer over serial isn't compatible with rfm12 debug over uart"
#endif


#include "apps.h"

// Defini pour le tarif heures creuses...

#define TI_ADCO 		(1 << 0)
#define TI_OPTARIF 	(1 << 1)
#define TI_ISOUSC 	(1 << 2)
#define TI_IND_HCHC	(1 << 3)
#define TI_IND_HCHP	(1 << 4)
#define TI_PTEC      (1 << 5)
#define TI_IINST     (1 << 6)
#define TI_ADPS      (1 << 7)
#define TI_IMAX      (1 << 8)
#define TI_PAPP      (1 << 9)
#define TI_HHPHC     (1 << 10)
#define TI_MOTDETAT  (1 << 11)

// Not optimized for memory usage, more for performance!
typedef struct {
	uint16_t config;
	char adco[13];
	char optarif[5];
	char isousc[3];
	char ind_hchc[10];
	char ind_hchp[10];
	char ptec[5];
	char iinst[4];
	char adps[4];
	char imax[4];
	char papp[6];
	char hhphc[2];
	char motdetat[7];
} teleinfo_values_t;
	
#define check_reader()  				\
	do { 										\
		if (number_read >= registered_dev) { \
			teleinfo_get_frame();		\
		}										\
		number_read++;						\
	} while (0)

void teleinfo_init(void *cfg);

int8_t teleinfo_get_adco(struct packet_t *);
int8_t teleinfo_get_optarif(struct packet_t *);
int8_t teleinfo_get_isousc(struct packet_t *);
int8_t teleinfo_get_ind_hchc(struct packet_t *);
int8_t teleinfo_get_ind_hchp(struct packet_t *);
int8_t teleinfo_get_ptec(struct packet_t *);
int8_t teleinfo_get_iinst(struct packet_t *);
int8_t teleinfo_get_adps(struct packet_t *);
int8_t teleinfo_get_imax(struct packet_t *);
int8_t teleinfo_get_papp(struct packet_t *);
int8_t teleinfo_get_hhphc(struct packet_t *);
int8_t teleinfo_get_motdetat(struct packet_t *);

#endif
