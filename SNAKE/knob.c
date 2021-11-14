//knob functionality code - PB8 and PB9 accepts left(CCW) and right(CW) input and translates that to snake direction.
#include "main.h"

static bool knobWhileLoop;
static bool hasWritten = false;
void gpio_init()
{
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE8_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE8_Pos; // PB8 Digital INPUT
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD8_Msk;
	GPIOB->PUPDR |= 0x01 << GPIO_PUPDR_PUPD8_Pos; // Pull-up engaged
	GPIOB->MODER &= ~GPIO_MODER_MODE9_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE9_Pos; // PB9 Digital INPUT
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD9_Msk;
	GPIOB->PUPDR |= 0x01 << GPIO_PUPDR_PUPD9_Pos; // Pull-up engaged
}

void knob(void)
{
	int16_t msg;
	msg =2;
	static struct btn_struct quad_A = {.mask_for_btn= 0<<8, 
																		.pin_ptr = &(GPIOB->IDR),
																		.state = UP};  
	
	static struct btn_struct quad_B = {.mask_for_btn= 0<<9, 
																		.pin_ptr = &(GPIOB->IDR),
																		.state = UP}; 
	enum btn_edge eA; 
	enum btn_edge eB;

	init_btn(1 << 8, &(GPIOB->IDR), &quad_A);  // Init state machine for PB8
	init_btn(1 << 9, &(GPIOB->IDR), &quad_B);	 // Init state machine for PB9
															
	static bool knob_initialization;																	
	if(knob_initialization == false) //makes gpio_init() run only once when the game is started and resets
	{
		gpio_init();
		knob_initialization = true;
	}
	
	knobWhileLoop = true;
	while(knobWhileLoop == true)
	{
		for(int32_t i =0; i < 22345; i++) //sets speed of snake and makes sure an input can only be accepted/read for .02 seconds
		{
			eA = update_btn(&quad_A);	//check and update the state for eA
			if(eA == ACTIVE)
			{
				for(int32_t i=0; i<1; i++) //makes sure you cannot crank the knob and have the snake go in circles really quick
				{													//one knob turn is one input
					eB = update_btn(&quad_B); //check and update the state for eB
					if(eB == INACTIVE)
					{
						msg = 1;
						hasWritten = true;
					}
					else if(eB==ACTIVE)
					{
						msg = 3;
						hasWritten = true;
					}
				}
			}
		}
		if(hasWritten == false) {msg = 2;} //if nothing is being written the snake continues straight
		write_q(&Direction, msg);
		hasWritten = false;
		knobWhileLoop = false;
	}
	
}


