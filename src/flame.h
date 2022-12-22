#ifndef __flame_h
#define __flame_h


/**********************************************************
 * This is a serson for flame, and you just init a gpio and 
 * and will be callback at step ISR. So if the code is run at 
 * extern Flash, you must know how long at ISR
 * *******************************************************/

#include "main.h"

/*
#define BOARD_FLAME_PORT
#define BOARD_FLAME_PIN
*/

#ifdef BOARD_FLAME_PORT
#define FLAME_PORT                  BOARD_FLAME_PORT
#define FLAME_PIN                   BOARD_FLAME_PIN
#endif

#endif
