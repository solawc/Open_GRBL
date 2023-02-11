/*
 debug.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __debug_h
#define __debug_h

#include "../../main.h"

#define DEBUG_SWITCH 
#ifdef DEBUG_SWITCH
#define DEBUG_ERROR(fmt,arg...)         do{printf("---error--- [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)         do{printf("---debug--- [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)   
#define DEBUG_PRINTF(fmt, arg...)       do{printf(fmt, ##arg);}while(0)  
#else 
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#define DEBUG_PRINTF(fmt, arg...) 
#endif /* DEBUG_SWITCH */

#endif