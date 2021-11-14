#include <stdio.h>
#include <stdlib.h>
#include "stm32l053xx.h"
#include <stdint.h>

void config_io(void); //GPIO pin13 configuration. config_io();
void led(void); //main function for led, has TIM21 configuration changes LED brightness. led();
