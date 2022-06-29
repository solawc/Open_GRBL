#ifndef __grbl_config_h
#define __grbl_config_h

/*******************************************************
 * Here is config st_grbl if want to enable fetura
 * ****************************************************/

// #define LCD_TFT_SUPPORT
#ifdef LCD_TFT_SUPPORT
    // #define LCD_MKS_TS35
    #ifdef LCD_MKS_TS35
        #define HAS_TS35_CFG
    #endif

    // #define LCD_MKS_TS24
    #ifdef LCD_MKS_TS24
        #define HAS_TS24_CFG
    #endif
#endif

#define SDSUPPORT
#ifdef SDSUPPORT
    #define HAS_SDCARD
#endif

/*******************************************************
 * For LCD Controller UI, and you must define LCD,
 * example :LCD_MKS_TS35 or LCD_MKS_TS24
 * ****************************************************/
// #define USE_LVGL_UI
#ifdef USE_LVGL_UI
    #define HAS_LVGL_UI
#endif


#endif 
