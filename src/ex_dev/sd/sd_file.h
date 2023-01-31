#ifndef __sd_file_h
#define __sd_file_h

#include "../../main.h"

#define SD_FILE_PATH            "1:"

#define CMD_SD_INSER            "SD_INSER\n"
#define CMD_SD_OUT              "SD_OUT\n"
#define CMD_SD_OK               "SD_OK\n"
#define CMD_SD_EMPTY            "SD_EMPTY\n"
#define CMD_SD_ERROR            "SD_ERROR\n"


#define FILE_CMD_LIMIT          96
#define TEST_PATH_FILE          "1:pic1.nc"

extern bool                     sd_ready_next;  
extern uint32_t                 sd_current_line_number; 

typedef enum {
    SD_STATE_IDLE,                  /* SD卡空闲状态        */    
    SD_STATE_NOT_PRESENT,           /* SD卡没有插入        */    
    SD_STATE_BUSY,                  /* SD卡忙状态          */
    SD_STATE_PRINTING,              /* SD卡打印中          */
    SD_STATE_WRITETING,             /* SD卡写入数据的过程  */        
    SD_STATE_PARSING,               /* SD卡等待解析的过程  */            
}sd_state_t;
extern sd_state_t   sd_state;


void sd_init(void);
void sd_state_check(void);
void get_fafts_info(void);
bool get_sd_state(void);


// for fatfs function
void sd_list(const char *path);
bool sd_open_file(const char *path);
bool sd_close_file();
bool sd_read_line(char *line);

// for report msg function  
void sd_report_state(void);
void sd_report_open_file(char *line);
void sd_report_mem(void);



#endif
