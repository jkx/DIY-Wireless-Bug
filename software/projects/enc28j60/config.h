#ifndef CONFIG_H
#define CONFIG_H

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define FWVERSION 1
#define FWVERSION_STR "" STR(FWVERSION)

void config_init();

struct config_t {
        uint8_t address;
	uint8_t mac[6];
	uint16_t udp_dstport;
        char collector[64];
};

extern struct config_t config;

#endif
