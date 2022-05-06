#include "hal_debug.h"


void test_st_timer_hight(void) {

    hal_set_timer_init();
    hal_set_timer_irq_enable();
}



void debug_mode_inter(void) {
    
    test_st_timer_hight();
}