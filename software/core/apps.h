#ifndef APPS_H
#define APPS_H

typedef struct {
	void (*init)(void*);
	int16_t (*get)(void);
	void (*set)(int16_t);
	void *cfg;
} application_t;

void set_apps(application_t* apps, uint8_t size);
application_t* get_app(uint8_t sensor);

#endif
