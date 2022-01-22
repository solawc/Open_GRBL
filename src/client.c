#include "client.h"

client_buff_t client_rb[CLIENT_MAX];

void client_init(uint8_t client) {

    client_rb[client].head = 0;
    client_rb[client].tail = 0;
    client_rb[client].len = 0;

}

void client_write(uint8_t client, uint8_t wdata) {

    

}

void client_read(uint8_t client, uint8_t *rdata) {


}

void client_read_buff(uint8_t client, uint8_t buff) {

    
}


