
#include "stm32l053xx.h"
#include "stdint.h"
#include "fsm_btn.h"

void gpio_init(void); //GPIO configuration for Pins 8 and 9. gpio_init();
void knob(void); //accepts user input to change snake direction. knob();