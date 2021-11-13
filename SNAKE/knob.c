// Demo of input-interpreter state machine.
// carroll@trine.edu 2021.9.20
// REQUIRED HARDWARE================
// Active-low btn on PB3 = N.O. momentary between PB3 & ground
// NUCLEO LABELING (PB3 is Arduino Header PWM/D3)

#include "stm32l053xx.h"
#include "stdint.h"
#include "fsm_btn.h"
#include "main.h"


void gpio_init(void);
int knob(void);
static bool knobWhileLoop;
static bool hasWritten = false;
// Config PB3 as input with pull-up.
// Config PA5 as output to Nucleo "user" LED
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
    
    //RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    //GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    //GPIOA->MODER |= 1 << GPIO_MODER_MODE5_Pos;  // PA5 DIGITAL OUTPUT    
	
	//-------------------------------------------------------------------------
	
	
    GPIOB->MODER &= ~GPIO_MODER_MODE12_Msk;
    GPIOB->MODER |= 1 << GPIO_MODER_MODE12_Pos;
	
	
	//-------------------------------------------------------------------------
	
	
	
}


int knob()
{
	int16_t msg;
	msg =2;
	GPIOB->BSRR = GPIO_BSRR_BS_12;
	
	
	
	
    static struct btn_struct quad_A = {.mask_for_btn= 0<<8, 
                                      .pin_ptr = &(GPIOB->IDR),
                                      .state = UP};  
		
		static struct btn_struct quad_B = {.mask_for_btn= 0<<9, 
                                      .pin_ptr = &(GPIOB->IDR),
                                      .state = UP}; 
    // static and automatic are the same only in MAIN().
	enum btn_edge eA; 
	enum btn_edge eB;
									  
    //gpio_init();
    init_btn(1 << 8, &(GPIOB->IDR), &quad_A);  // Init state machine for PB8
		init_btn(1 << 9, &(GPIOB->IDR), &quad_B);	 // Init state machine for PB9
																			
																			
		static bool knob_initialization;	
																			
		if(knob_initialization == false)
		{
			gpio_init();
			knob_initialization = true;
		}
    
		knobWhileLoop = true;
    while(knobWhileLoop == true)
		{
			
			
			for(int32_t i =0; i < 123456; i++)
			{
				if(hasWritten == false)
				{
					
			
			eA = update_btn(&quad_A);
			if(eA == ACTIVE)
			{
				//for(int32_t i=0; i<1; i++) //for loop of range 1 makes a knob turn only 'active' for one turn. wont continue to make snake turn in circles.
				//{														//all if statements could potentially be inside for loop.
																//this has not been tested, so not entirely sure if this actually works
					eB = update_btn(&quad_B);
					if(eB == INACTIVE)
					{
						//GPIOA->ODR = 0 << 5;
						msg = 1;
						hasWritten = true;
					}
					else if(eB==ACTIVE)
					{
						//GPIOA->ODR = 1<<5;
						msg = 3;
						hasWritten = true;
						
					}
				
				//}
			}
		}
	}
			if(hasWritten == false) {msg = 2;}
				
			write_q(&Direction, msg);
			
			
			
			//GPIOB->BSRR = GPIO_BSRR_BS_12;
			knobWhileLoop = false;
		}
		GPIOB->BSRR = GPIO_BSRR_BR_12;
}


