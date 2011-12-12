#ifndef APPS_H
#define APPS_H

struct data_t {
	char *packet;
	char *buf;
	uint8_t remaining_len;
};

typedef struct {
	void (*init)(void*);
	int8_t (*get)(struct data_t*);
	void (*set)(struct data_t*);
	void *cfg;
} application_t;


void set_apps(application_t* apps, uint8_t size);
application_t* get_app(uint8_t sensor);

#endif
