// Demo of input-interpreter state machine.
// carroll@trine.edu 2021.9.20
// REQUIRED HARDWARE================
// Active-low btn on PB3 = N.O. momentary between PB3 & ground
// NUCLEO LABELING (PB3 is Arduino Header PWM/D3)

#include "stm32l053xx.h"
#include "stdint.h"
#include "fsm_btn.h"


void gpio_init(void);
int knob(void);
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
    
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    GPIOA->MODER |= 1 << GPIO_MODER_MODE5_Pos;  // PA5 DIGITAL OUTPUT    
}


int knob( )
{
    static struct btn_struct quad_A = {.mask_for_btn= 0<<8, 
                                      .pin_ptr = &(GPIOB->IDR),
                                      .state = UP};  
		
		static struct btn_struct quad_B = {.mask_for_btn= 0<<9, 
                                      .pin_ptr = &(GPIOB->IDR),
                                      .state = UP}; 
    // static and automatic are the same only in MAIN().
	enum btn_edge eA; 
	enum btn_edge eB;
									  
    gpio_init();
    init_btn(1 << 8, &(GPIOB->IDR), &quad_A);  // Init state machine for PB8
		init_btn(1 << 9, &(GPIOB->IDR), &quad_B);	 // Init state machine for PB9
    
    while(1)
		{
			eA = update_btn(&quad_A);
			if (eA == ACTIVE)
			{
				eB = update_btn(&quad_B);
				if(eB == INACTIVE)
				{
					GPIOA->ODR = 0 << 5; // Toggle off LED
				}
				
				else if(eB==ACTIVE)
				{GPIOA->ODR = 1<<5;}
				
			}
		}
}
