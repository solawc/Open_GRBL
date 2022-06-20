#ifndef __sd_file_h
#define __sd_file_h

#include "../../main.h"

#define SD_FILE_PATH        "1:"

#define CMD_SD_INSER        "SD_INSER\n"
#define CMD_SD_OUT          "SD_OUT\n"
#define CMD_SD_OK           "SD_OK\n"
#define CMD_SD_EMPTY        "SD_EMPTY\n"
#define CMD_SD_ERROR        "SD_ERROR\n"



void sd_init(void);
void sd_state_check(void);
void get_fafts_info(void);


// test
void sd_list();
#endif
