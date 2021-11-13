//implement interrupt in main.c. when fruit is hit interrupt starts and communicates to led
#include "led.h"
#include "main.h"

void config_gpio(void)
{
	RCC->IOPENR|=RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~(GPIO_MODER_MODE13_Msk);
	GPIOB->MODER |= 2<<GPIO_MODER_MODE13_Pos;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_13);
	GPIOB->AFR[1] |= (0x06 << GPIO_AFRH_AFSEL13_Pos);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD13_Msk);
}

int led(void)
{
	
	
	int16_t msg;
	//bool queueContents;
	//queueContents = read_q(&light , &msg);
	read_q(&light, &msg);
	
	msg = 500-(msg*25);
	
	//if(queueContents == true)
	//{
	TIM21->ARR = msg; //low numbers = bright, high numbers = dim
		
	
	
	config_gpio();
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;
	TIM21->PSC = 15; //prescale to 15, so APBCLK/16 = 1MHz
	TIM21->CCR1 = 4; //signal high for 4us
	TIM21->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; //pwm mode 1 (110) preload enabled (1), active high polarity
	TIM21->CCER |= TIM_CCER_CC1E;
	TIM21->CR1 |= TIM_CR1_CEN; //enable counter
	TIM21->EGR |= TIM_EGR_UG; //force update
		
	//}
	
	
	
	
	
}
