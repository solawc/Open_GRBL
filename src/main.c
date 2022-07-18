/*
  main.c - rs274/ngc parser.
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

#include "main.h"

int main() {

  grblHwInit();

  clientInit();

#ifdef STM32G0B0xx
  // here must wait for some time, beacuse STM32G0B0CE have no XTAL
  HAL_Delay(100);  
#endif

  // report MCU info and you can check
  grblReprotMcuInfo();

  // Begin GRBL Task
  grblTaskInit();

#if defined(USE_FREERTOS_RTOS)
  osKernelStart();
#endif
}

void _delay_ms(uint32_t tick) {
  
#if defined(USE_FREERTOS_RTOS)
  vTaskDelay(tick);
#else 
  uint32_t mililoop = SystemCoreClock / 1000;
	for (uint32_t i=0; i< mililoop; i++)
		__asm__ __volatile__("nop\n\t":::"memory");
  // HAL_Delay(tick);
#endif
}

void _delay_us(uint32_t tick) {
  while(tick--) {
	  __NOP();
  }
}
