#include "sd_file.h"

FIL fil;

void sd_init(void) {

    FATFS fs;
    
    FRESULT fs_res;

    hal_sd_register();

    if(!hal_sd.sd_get_status()) {
        fs_res = f_mount(&fs,"1:",1);
        if(fs_res == FR_OK){
            hal_sd.is_has_sd = 1;
        }else {
             hal_sd.is_has_sd = 0;
        }
    }else{
        hal_sd.is_has_sd = 0; 
    }
}

void sd_state_check(void) {

    /* 确保SD是插入稳定的 */
    if(!hal_sd.sd_get_status()) {
        if(hal_sd.is_has_sd == 1) printf("SDCard Ok\n");
        else { printf("SDCard Error\n"); }

    }else{
        if(hal_sd.is_has_sd == 1) printf("No SDCard\n");
    }
}


bool sd_mount(void) {

    FATFS fs;
    FRESULT fs_res;
    fs_res = f_mount(&fs,"1:",1);
    if(fs_res == FR_OK) return true;
    else return false;
}