#ifndef __cpu_stm32f4_map_h
#define __cpu_stm32f4_map_h

#include "grbl.h"

#define STM32F429XX

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_PORT       GPIOB
#define X_STEP_BIT      1  
#define Y_STEP_BIT      2  
#define Z_STEP_BIT      3
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_PORT    GPIOA
#define X_DIRECTION_BIT   0 
#define Y_DIRECTION_BIT   1  
#define Z_DIRECTION_BIT   2
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_PORT   GPIOA
#define STEPPERS_DISABLE_BIT    1
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)
// #define SetStepperDisableBit() GPIO_SetBits(STEPPERS_DISABLE_PORT,STEPPERS_DISABLE_MASK)
// #define ResetStepperDisableBit() GPIO_ResetBits(STEPPERS_DISABLE_PORT,STEPPERS_DISABLE_MASK)


  // Define homing/hard limit switch input pins and limit interrupt vectors. 
  // NOTE: All limit bit pins must be on the same port
#define LIMIT_PORT       GPIOB
#define X_LIMIT_BIT       0  
#define Y_LIMIT_BIT       13  
#define Z_LIMIT_BIT       14  
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

  // Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_PORT   GPIOB
#define RCC_SPINDLE_ENABLE_PORT RCC_APB2Periph_GPIOB
#define SPINDLE_ENABLE_BIT    13  // 
#ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
#define SPINDLE_DIRECTION_DDR   GPIOB
#define SPINDLE_DIRECTION_PORT  GPIOB
#define SPINDLE_DIRECTION_BIT   14  // 
#endif
#define SetSpindleEnablebit()       GPIO_WriteBit(SPINDLE_ENABLE_PORT, 1 << SPINDLE_ENABLE_BIT, Bit_SET)
#define ResetSpindleEnablebit()     GPIO_WriteBit(SPINDLE_ENABLE_PORT, 1 << SPINDLE_ENABLE_BIT, Bit_RESET)
#define SetSpindleDirectionBit()    GPIO_WriteBit(SPINDLE_DIRECTION_PORT, 1 << SPINDLE_DIRECTION_BIT,Bit_SET)
#define ResetSpindleDirectionBit()  GPIO_WriteBit(SPINDLE_DIRECTION_PORT, 1 << SPINDLE_DIRECTION_BIT,Bit_RESET)

  // Define flood and mist coolant enable output pins.
  // a later date if flash and memory space allows.
// #define COOLANT_FLOOD_PORT            GPIOB
// #define RCC_COOLANT_FLOOD_PORT        RCC_APB2Periph_GPIOB
// #define COOLANT_FLOOD_BIT             3  
// #define COOLANT_MIST_PORT             GPIOB
// #define RCC_COOLANT_MIST_PORT         RCC_APB2Periph_GPIOB
// #define COOLANT_MIST_BIT              4 

  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
// #define CONTROL_PIN_PORT              GPIOB
// #define CONTROL_PORT                  GPIOB
// #define RCC_CONTROL_PORT              RCC_APB2Periph_GPIOB
// #define GPIO_CONTROL_PORT             GPIO_PortSourceGPIOB
// #define CONTROL_RESET_BIT             5  
// #define CONTROL_FEED_HOLD_BIT         6  
// #define CONTROL_CYCLE_START_BIT       7  
// #define CONTROL_SAFETY_DOOR_BIT       8  
// #define CONTROL_MASK                 ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))

  // Define probe switch input pin.
// #define PROBE_PORT                    GPIOA
// #define RCC_PROBE_PORT                RCC_APB2Periph_GPIOA
// #define PROBE_BIT                     15 
// #define PROBE_MASK                    (1<<PROBE_BIT)

  // Start of PWM & Stepper Enabled Spindle
// #ifdef VARIABLE_SPINDLE
//   // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
// #define SPINDLE_PWM_FREQUENCY       10000                   // KHz
// #define SPINDLE_PWM_DDR	            GPIOA
// #define SPINDLE_PWM_PORT            GPIOA
// #define RCC_SPINDLE_PWM_PORT        RCC_APB2Periph_GPIOA
// #define SPINDLE_PWM_BIT	            8    
// #endif // End of VARIABLE_SPINDLE
// #define SPINDLE_PWM_MAX_VALUE       (1000000 / SPINDLE_PWM_FREQUENCY)
// #ifndef SPINDLE_PWM_MIN_VALUE
// #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
// #endif
// #define SPINDLE_PWM_OFF_VALUE     0
// #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

#endif
