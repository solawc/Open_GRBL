#include "led_task.h"

TaskHandle_t led_task_handle = NULL;

void f_led_task(void *parg)   {
	hal_led_gpio_init();

	while(1) {
		// hal_led_toggle();
		vTaskDelay(500);
	}
}

void led_task_creat(void) {
	BaseType_t status = pdPASS;
	xTaskCreate(f_led_task,
				"led task",
				1024,
				NULL,
				1,
				&led_task_handle);
	if(status == pdPASS) {
	}
	else  {
		
	}
}



















