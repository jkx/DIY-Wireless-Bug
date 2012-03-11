#ifndef BUGONE_H
#define BUGONE_H

#include "board.h"
#include "apps.h"

#define BUGONE_PACKET_SIZE 32

void bugone_init(const application_t* applications, uint8_t nb_devices);

#endif
