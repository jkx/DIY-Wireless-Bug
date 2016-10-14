#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "apps.h"

static application_t* _apps;
static uint8_t _size;

void apps_set(application_t* apps, uint8_t size) {
    _apps = apps;
    _size = size;
}

application_t* app_get(uint8_t device) {
    if (device < _size)
        return &_apps[device];
    else
        return NULL;
}


void apps_setup(application_t* apps) {
    uint8_t nb_devices=0;
    application_t *app=apps;

    /* Count how many devices are declared */
    while (!((app->init == NULL) &&
             (app->get == NULL) &&
             (app->set == NULL) &&
             (app->cfg == NULL))) {
        nb_devices++;
        app++;
    }
    apps_set(apps,nb_devices);
}



void apps_init() {
    uint8_t i=0;

    for (i=0 ; i < _size; i++) {
        if (_apps[i].init == NULL) {
            continue;
        }
        _apps[i].init(_apps[i].cfg);
    }
}
