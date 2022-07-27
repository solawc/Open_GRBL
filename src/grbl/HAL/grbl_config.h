/*
  grbl_config.h
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2021-2022 sola

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

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

    // #define W25QXX_FLASH_SUPPORT
    #ifdef W25QXX_FLASH_SUPPORT
        #define HAS_W25Qxx
    #endif


    // #define SDSUPPORT
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


    // #define USE_WDG
    #ifdef USE_WDG
        #define HAS_WDG
    #endif

#endif 
