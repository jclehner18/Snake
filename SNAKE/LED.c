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
#include "queue.h"

void config_io(void);
//void config_timer21(void);

void config_gpio(void)
{
	RCC->IOPENR|=RCC_IOPENR_GPIOCEN;
	GPIOC->MODER &= ~(GPIO_MODER_MODE0_Msk);
	GPIOC->MODER |= 1<<GPIO_MODER_MODE0_Pos;
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_0);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk);
}

/*void config_timer21(void)
{
	//pretty sure this is configured correcty for pwm
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;
	TIM21->PSC = 15; //prescale to 15, so APBCLK/16 = 1MHz
	TIM21->ARR = 8; //set ARR = 8 since timer is 1MHz the period is 9us
	TIM21->CCR1 = 4; //signal high for 4us
	TIM21->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; //pwm mode 1 (110) preload enabled (1), active high polarity
	TIM21->CCER |= TIM_CCER_CC1E;
	TIM21->CR1 |= TIM_CR1_CEN; //enable counter
	TIM21->EGR |= TIM_EGR_UG; //force update
}*/


int led(void) //main file for this file
{
	config_gpio();
	//config_timer21();
	
	while(1)  //----------maybe we can just have the led blink when a collision happens-----------
	{
		//this just makes led blink, not change brightness
		GPIOC->BSRR = GPIO_BSRR_BS_0;
		for(volatile int32_t n=0; n<200000; n++);
		GPIOC->BSRR = GPIO_BSRR_BR_0;
		for(volatile int32_t n=0; n<200000; n++);
	}
}
