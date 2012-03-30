#include "bugOne.h"

extern application_t applications[];

int main(void) {
    bugone_init(applications);

    while (1) {
        bugone_loop();
    }
}
