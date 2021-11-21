#ifndef __client_h
#define __client_h

#include "grbl_hal.h"



/*
 * define user client, and they will use different buff,
 * and task will aks and answan client back.
*/
#define CLIENT_SERIAL           0X00
#define CLIENT_WIFI             0X01
#define CLIENT_LCD              0X02
#define CLIENT_SD               0X03
#define CLIENT_MAX              4

#define RB_BUFF_SEIZ            1024

typedef struct {

    bool        _is_rb_full;
    bool        _is_rb_err;
    uint8_t     head;
    uint8_t     tail;
    uint8_t     rb_buff[RB_BUFF_SEIZ];
    uint32_t    length;
}ringbuff_t;

typedef struct {

    bool        _is_client_busy;
    bool        _is_client_full;
    uint8_t     client_buff[CLIENT_MAX];

}clinet_t;



#endif
