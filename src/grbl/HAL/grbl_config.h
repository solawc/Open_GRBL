#ifndef __grbl_config_h
#define __grbl_config_h

/*
 * Here is config st_grbl if want to enable fetura
 *
*/
// #define LCD_MKS_TS35
#ifdef LCD_MKS_TS35
    #define HAS_TS35_CFG
#endif

// #define LCD_MKS_TS24
#ifdef LCD_MKS_TS24
    #define HAS_TS24_CFG
#endif


#define LCD_TFT_SUPPORT
#ifdef LCD_TFT_SUPPORT
    #define HAS_LCD_TFT_CFG
#endif

#define SDSUPPORT
#ifdef SDSUPPORT
    #define HAS_SDCARD
#endif

#endif 
