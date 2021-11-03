//LED code will appear here
//adjust the brightness of the led when a fruit is hit.
//need pwm
//need to adjust duty cycle
//implement interrupt in main.c. when fruit is hit interrupt starts and communicates to led


//use tim21
//use gpio PC0

#include <stdio.h>
#include <stdlib.h>
#include "stm32l053xx.h"
#include <stdint.h>

void config_io(void);
void config_timer21(void);

void config_io(void)
{
	
}

void config_timer21(void)
{
	
}


//simpl blinky program to make sure GPIO port for led is functioning properly
//weird thing: doesnt run when function is named led. but run when named main
//knob also doesnt work when its 'main' function is named knob
int led(void) //main file for this file
{
	//pc0
	RCC->IOPENR|=RCC_IOPENR_GPIOCEN;
	
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE0_Msk);
	GPIOC->MODER |= 1<<GPIO_MODER_MODE0_Pos;
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_0);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk);

	
	while(1)
	{
		GPIOC->BSRR = GPIO_BSRR_BS_0;
		for(volatile int32_t n=0; n<200000; n++);
		GPIOC->BSRR = GPIO_BSRR_BR_0;
		for(volatile int32_t n=0; n<200000; n++);
	}
}
