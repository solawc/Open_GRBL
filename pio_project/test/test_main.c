#include <unity.h>
#include "../src/main.h"


void led_init(void) {

    GPIO_InitTypeDef GPIO_Init; 
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pin = GPIO_PIN_10;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOH, &GPIO_Init);
}

void hal_led_on(void) {
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_RESET);
}

void hal_led_off(void) {
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_SET);
}

void hal_led_toggle(void) {
	HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);
}




void setUp(void) {
    led_init();
}

void tearDown(void) {
    hal_led_off();
}

void test_led_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(GPIO_PIN_10, GPIO_PIN_10);
}

void test_led_state_high(void) {
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_SET);
    TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_10));
}

void test_led_state_low(void) {
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_RESET);
    TEST_ASSERT_EQUAL(GPIO_PIN_RESET, HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_10));
}

int main() {
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay
    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_pin_number);

    for (unsigned int i = 0; i < 5; i++)
    {
        RUN_TEST(test_led_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_state_low);
        HAL_Delay(500);
    }

    UNITY_END(); // stop unit testing

    while(1){}
}

void SysTick_Handler(void) {
    HAL_IncTick();
}