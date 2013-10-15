#ifndef BUGONE_H
#define BUGONE_H

#include "board.h"
#include "apps.h"

#define BUGONE_PACKET_SIZE 32

void bugone_init(application_t* applications);
void bugone_setup_watchdog(int val);
void bugone_deep_sleep();

#endif
