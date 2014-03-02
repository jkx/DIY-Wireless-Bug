#include "bugOne.h"

extern application_t applications[];
extern int send_flush;

int bugone_main(void) {
    bugone_init(applications);
    uint16_t i;

    while (1) {
        bugone_loop();
        i++;
        if (i>10000) {
            send_flush=0;
        }
    }
}
