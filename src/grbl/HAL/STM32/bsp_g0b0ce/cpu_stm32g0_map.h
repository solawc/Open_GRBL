#ifndef __cpu_stm32g0_map_h
#define __cpu_stm32g0_map_h

#include "../../grbl/grbl.h"

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define X_STEP_BIT      0  
#define Y_STEP_BIT      1  
#define Z_STEP_BIT      2
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
#define X_DIRECTION_BIT   0 
#define Y_DIRECTION_BIT   1  
#define Z_DIRECTION_BIT   2
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_BIT    1
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port
#define X_LIMIT_BIT       0  
#define Y_LIMIT_BIT       1  
#define Z_LIMIT_BIT       2  
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits


/*************************************************************************
 * Allow laser output 0-10000Hz
 * **********************************************************************/
#define SPINDLE_PWM_FREQUENCY       1000                   
#define SPINDLE_PWM_MAX_VALUE       (1000000 / SPINDLE_PWM_FREQUENCY)
#ifndef SPINDLE_PWM_MIN_VALUE
#define SPINDLE_PWM_MIN_VALUE       1   // Must be greater than zero.
#endif
#define SPINDLE_PWM_OFF_VALUE       0
#define SPINDLE_PWM_RANGE           (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

#endif