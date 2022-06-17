#include "sd_file.h"

FIL fil;
FATFS fs;

void sd_init(void) {

    // FATFS fs;
    
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

    sd_state_check();
    get_fafts_info();
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

    
    FRESULT fs_res;
    fs_res = f_mount(&fs,"1:",1);
    if(fs_res == FR_OK) return true;
    else return false;
}

void get_fafts_info( void )
{
    FATFS *pfs = &fs;

    DWORD fre_clust, fre_size, tot_size;
    
    uint8_t result = f_getfree( "1:", &fre_clust, &pfs );
    
    if( result == FR_OK )
    {
        tot_size = (pfs->n_fatent - 2) * pfs->csize/2; // 总容量    单位Kbyte
        fre_size = fre_clust * pfs->csize/2;           // 可用容量  单位Kbyte

        hal_sd.sd_all_size = tot_size/1024;
        hal_sd.sd_free_size = fre_size/1024;
        printf("SDCard Size: %lu MB\r\n", hal_sd.sd_all_size );
        printf("SDFree Size: %lu MB\r\n", hal_sd.sd_free_size );
  }
    else{
        printf("Can't check SDcard:%d\r\n", result );
    }
}

char *sd_read_line(void) {

    char *line = 0;

    return line;
}



