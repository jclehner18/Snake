//LED code will appear here
//adjust the brightness of the led when a fruit is hit.
//need pwm
//need to adjust duty cycle
//implement interrupt in main.c. when fruit is hit interrupt starts and communicates to led


//use tim21
//use gpio PC0

#include "led.h"
#include "main.h"

void config_gpio(void)
{
	/*RCC->IOPENR|=RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~(GPIO_MODER_MODE13_Msk);
	GPIOB->MODER |= 1<<GPIO_MODER_MODE13_Pos;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_13);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD13_Msk); */
	
	RCC->IOPENR|=RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~(GPIO_MODER_MODE13_Msk);
	GPIOB->MODER |= 2<<GPIO_MODER_MODE13_Pos;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_13);
	GPIOB->AFR[1] |= (0x06 << GPIO_AFRH_AFSEL13_Pos);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD13_Msk);
	
}

/*void config_timer21(void)
{
	//pretty sure this is configured correcty for pwm
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;
	TIM21->PSC = 15; //prescale to 15, so APBCLK/16 = 1MHz
	//TIM21->ARR = 800; //set ARR = 8 since timer is 1MHz the period is 9us
	TIM21->CCR1 = 4; //signal high for 4us
	TIM21->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; //pwm mode 1 (110) preload enabled (1), active high polarity
	TIM21->CCER |= TIM_CCER_CC1E;
	TIM21->CR1 |= TIM_CR1_CEN; //enable counter
	TIM21->EGR |= TIM_EGR_UG; //force update
}*/

/*void lightup(int32_t x)
{
	if(x==1)
	{
		GPIOC->BSRR = GPIO_BSRR_BS_0;
		for(volatile int32_t n=0; n<200000; n++);
		GPIOC->BSRR = GPIO_BSRR_BR_0;
	}
}*/

void brightness(int32_t x);
/*void brightness(int32_t x)
{
	if(x == !NULL) //x is the value that will determine brightness. if msg is not empty
	{
		TIM21->ARR = x;
	}
}*/

int led(void) //main file for this file
{
	config_gpio();
	//config_timer21();
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;
	TIM21->PSC = 15; //prescale to 15, so APBCLK/16 = 1MHz
	//TIM21->ARR = 800; //set ARR = 8 since timer is 1MHz the period is 9us
	TIM21->CCR1 = 4; //signal high for 4us
	TIM21->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; //pwm mode 1 (110) preload enabled (1), active high polarity
	TIM21->CCER |= TIM_CCER_CC1E;
	TIM21->CR1 |= TIM_CR1_CEN; //enable counter
	TIM21->EGR |= TIM_EGR_UG; //force update
	
	int16_t msg;
	read_q(&light, &msg);
	TIM21->ARR = msg;
	
	//brightness(msg);
	
	while(1)
	{
		//int16_t msg;
		//read_q(&light, &msg);
		
		//lightup(msg);
		//brightness(msg);
		
		//this just makes led blink, not change brightness
		//GPIOB->BSRR = GPIO_BSRR_BS_13;
		//for(volatile int32_t n=0; n<200000; n++);
		//GPIOB->BSRR = GPIO_BSRR_BR_13;
		//for(volatile int32_t n=0; n<200000; n++);
	}
}
