#include "sd_file.h"

FIL fil;
FATFS fs;

void sd_init(void) {

    // FATFS fs;
    
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

    sd_list();

    sd_open_file(TEST_PATH_FILE);
}

void sd_state_check(void) {

    /* 确保SD是插入稳定的 */
    if(!hal_sd.sd_get_status()) {
        if(hal_sd.is_has_sd == 1) printReturnInfo(CMD_SD_OK);
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
    // char inf_str[255];

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


bool sd_open_file(char *path) {

    FRESULT fr = FR_OK;

    char buff[96];

    fr = f_open(&fil, path, FA_READ);

    if(fr != FR_OK) return false;

    while(1) {  
        f_gets(buff, 96, &fil);
        printf("RB:%s", buff);
        // HAL_Delay(100);
    }
    return true;
}


char *sd_read_line(void) {

    char *line = 0;

    f_gets(line, FILE_CMD_LIMIT, &fil);

    return line;
}



/**************************************************
 * 这里是为了实现读取文件中途可以实现中途停止，以弱定义
 * 的形式来实现，可有可无；若需要这个功能，就重新定义实
 * 体.
 * ***********************************************/
__WEAK bool sd_list_state = true;
__WEAK bool sd_list_stop_cb() { return sd_list_state; }

void sd_list() {

    DIR dir;                    // 文件夹信息
    FILINFO fileinfo;           // 获取文件信息
    uint8_t result = 0;

    char fileName[255];

    result = f_opendir(&dir, SD_FILE_PATH);

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
                sprintf(fileName, "[File:%s, Size:%ldk]\n", fileinfo.fname, (fileinfo.fsize/1024));
                printReturnInfo(fileName);
            }
        }
    }else {
        printReturnInfo("SD_ERROR\n");
    }
}

