#ifndef __client_h
#define __client_h

#include "main.h"

#define CLIENT_SERIAL       0
#define CLIENT_SD           1
#define CLIENT_WIFI         2
#define CLIENT_ETH          3
#define CLIENT_MAX          4


typedef struct {

    uint32_t tail;
    uint32_t head;
    uint8_t buff[255];
    uint32_t len;

}client_buff_t;


void client_init(void);
bool client_write(uint8_t client, uint8_t wdata);
bool client_read(uint8_t client, uint8_t *rdata);

#endif