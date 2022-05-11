#include "client.h"

client_buff_t client_rb[CLIENT_MAX];

void client_init(void) {

    for(uint8_t i=0; i<CLIENT_MAX; i++) {
        client_rb[i].head = 0;
        client_rb[i].tail = 0;
        client_rb[i].len = 0;
    }
}

bool client_write(uint8_t client, uint8_t wdata) {

    if(client_rb[client].len >= 255) return false;

    client_rb[client].buff[client] = wdata;
    
    client_rb[client].tail = (client_rb[client].tail+1)%255;

    client_rb[client].len++;
    
    return true;
}

bool client_read(uint8_t client, uint8_t *rdata) {

    if(client_rb[client].len == 0) return false;

    *rdata = client_rb[client].buff[client];

    client_rb[client].head = (client_rb[client].head +1) % 255;

    client_rb[client].len--;

    return true;
}

void client_read_buff(uint8_t client, uint8_t buff) {

    
}


