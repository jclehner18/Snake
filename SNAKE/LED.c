//LED pwm code - the purpose of this code is to change the brightness of the led as a new fruit is picked up.
//it starts at the min brightness and gets brighter as fruits are picked up. 
#include "led.h"
#include "main.h"

static bool led_initialization =false;
void config_gpio(void)
{
	RCC->IOPENR|=RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~(GPIO_MODER_MODE13_Msk);
	GPIOB->MODER |= 2<<GPIO_MODER_MODE13_Pos;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_13);
	GPIOB->AFR[1] |= (0x06 << GPIO_AFRH_AFSEL13_Pos);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD13_Msk);
}

void led(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;
	if(led_initialization == false) //configuring the gpio at start if program only once so issues don't arrise
		{
			config_gpio();
			TIM21->ARR = 2000;  //initalizing a dimness of the led at the start of a new game, LED has a min dimness -- cannot ever appear to be off.
													//2000 just makes sure we are at that min brightness.
			led_initialization = true;
		}

	int16_t msg;
	bool queueContents;
	queueContents = read_q(&light , &msg); //msg is length in game code appendsnake()
	msg = 500-(msg*25);   	//this will icrease brightness on a factor of 20, since it is not very noticable to human eye. -------this code will actually meet out goal.
	//msg = 500-(msg*100);     //we are using this equation so you can tell a difference in brightness after each fruit pickup. -------this is for demonstration purposes.

	if(queueContents == true || queueContents == 1) //when a fruit is hit, length if snake is sent to queue, this checks for length of snake
	{																								//changes brightness when length increases
		TIM21->ARR = msg; //low numbers = bright, high numbers = dim
	}

	TIM21->PSC = 15; //prescale to 15, so APBCLK/16 = 1MHz
	TIM21->CCR1 = 4; //signal high for 4us
	TIM21->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; //pwm mode 1, preload enabled, active high polarity
	TIM21->CCER |= TIM_CCER_CC1E;
	TIM21->CR1 |= TIM_CR1_CEN; //enable counter
	TIM21->EGR |= TIM_EGR_UG; //force update
	
}
