#include "sd_file.h"

FIL             fil;                        
FATFS           fs;
bool            sd_ready_next = false;      // Grbl has processed a line and is waiting for another 
uint32_t        sd_current_line_number;     // stores the most recent line number read from the SD       
sd_state_t      sd_state;

void sd_init(void) {

    FRESULT fs_res;

    hal_sd_register();

    if(!hal_sd.sd_get_status()) {
        fs_res = f_mount(&fs,SD_FILE_PATH,1);
        if(fs_res == FR_OK){
            hal_sd.is_has_sd = 1;
        }else {
             hal_sd.is_has_sd = 0;
        }
    }else{
        hal_sd.is_has_sd = 0; 
    }

    sd_state_check();
    get_fafts_info();
}

void sd_state_check(void) {

    /* 确保SD是插入稳定的 */
    if(!hal_sd.sd_get_status()) {
        if(hal_sd.is_has_sd == 1) {
            sd_state = SD_STATE_IDLE;
            printReturnInfo(CMD_SD_OK);
        } 
        else { 
            printReturnInfo(CMD_SD_ERROR); 
            hal_sd.is_has_sd = 0;
        }
    }else{
        if(hal_sd.is_has_sd == 1) printReturnInfo(CMD_SD_EMPTY);
    }
}

bool sd_mount(void) {
    FRESULT fs_res;
    fs_res = f_mount(&fs,SD_FILE_PATH,1);
    if(fs_res == FR_OK) return true;
    else return false;
}

void get_fafts_info( void )
{
    FATFS *pfs = &fs;

    DWORD fre_clust, fre_size, tot_size;
    
    if(hal_sd.is_has_sd != 1) return;

    uint8_t result = f_getfree( SD_FILE_PATH, &fre_clust, &pfs );
    
    if( result == FR_OK )
    {
        tot_size = (pfs->n_fatent - 2) * pfs->csize/2; // 总容量    单位Kbyte
        fre_size = fre_clust * pfs->csize/2;           // 可用容量  单位Kbyte

        hal_sd.sd_all_size = tot_size/1024;
        hal_sd.sd_free_size = fre_size/1024;
        printReturnInfo(CMD_SD_INSER);
    }
    else{
        printReturnInfo(CMD_SD_ERROR);
    }
}

bool sd_open_file(const char *path) {

    FRESULT fr = FR_OK;
    fr = f_open(&fil, path, FA_READ);
    if(fr == FR_OK) {
        sd_ready_next = false;
        sd_state = SD_STATE_BUSY;
        return true;
    }
    else return false;
}

bool sd_close_file() {

    FRESULT fr = FR_OK;
    fr = f_close(&fil);
    if(fr == FR_OK) {
        sd_ready_next = false;
        return true;
    }
    else return false; 
}

bool sd_set_file_pos(uint32_t pos) {

    FRESULT fr = FR_OK;
    fr = f_lseek(&fil, pos);
    if(fr == FR_OK) return true;
    else return false;
}

bool sd_read_line(char *line) {

    if(f_gets(line, FILE_CMD_LIMIT, &fil) != 0 ) {

        return true;
    }else {
        return false;
    }
}

float sd_report_perc_complete() {

    return f_tell(&fil)/fil.obj.objsize;
}

bool get_sd_state(void) {

    if(!hal_sd.sd_get_status()) return true;
    else return false;
}



/**************************************************
 * 这里是为了实现读取文件中途可以实现中途停止，以弱定义
 * 的形式来实现，可有可无；若需要这个功能，就重新定义实
 * 体.
 * ***********************************************/
__WEAK bool sd_list_state = true;
__WEAK bool sd_list_stop_cb() { return sd_list_state; }

void sd_list(const char *path) {

    DIR dir;                    // 文件夹信息
    FILINFO fileinfo;           // 获取文件信息
    uint8_t result = 0;

    char fileName[1024];

    result = f_opendir(&dir, path);

    if(result == FR_OK) {
        while(f_readdir(&dir, &fileinfo)==FR_OK) {

            if(!sd_list_stop_cb()) return;

            if(fileinfo.fattrib & AM_DIR)  {
                if(fileinfo.fname[0]==0){ break; }
                sprintf(fileName, "[DIR:%s]\n", fileinfo.fname);
                printReturnInfo(fileName);
            }
            else {   
                if(fileinfo.fname[0]==0){ break; }
                sprintf(fileName, "[File:%s|SIZE:%ldk]\r\n", fileinfo.fname, (fileinfo.fsize/1024));
                printReturnInfo(fileName);
            }
        }
    }else {
        printReturnInfo("SD_ERROR\n");
    }
}

/***************************************************
 * 以下的函数作为Report相关返回
 * ************************************************/

// LG0200
void sd_report_state(void) {
    if(get_sd_state()) {
        printReturnInfo(CMD_SD_OK);
    }else{
        printReturnInfo(CMD_SD_EMPTY);
    }
}


// LG0201
/**************************************************
 * 当line被送进来时，它应该是一个完整的指令，例如：
 * [LG0201]1:
 * [LG0201]1:DIR/DIR/DIR...
 * 因此需要对径路参数做提取
 * ***********************************************/
void sd_report_open_file(char *line) {

    char *path = "1:";
    
    sd_list(path);
}

// LG0204
void sd_report_mem(void) {

    char cmd_str[128];

    sprintf(cmd_str, "SD_SIZE:%ldMB|%ldMB\n", hal_sd.sd_all_size, 
                                          hal_sd.sd_free_size);

    printReturnInfo(cmd_str);
}


