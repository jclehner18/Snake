// main file for running the schedule

#include "main.h"


queue_t Direction;// queue for use from knob to game logic
queue_t Locations;

queue_t light;

 //fixes Display() warning, not sure if this is misra compliant though




//knob timing


int main()
{
	//RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	//GPIOB->MODER &= ~GPIO_MODER_MODE12_Msk;
   // GPIOB->MODER |= 1 << GPIO_MODER_MODE12_Pos;
	
		//GPIOB->BSRR = GPIO_BSRR_BS_12;
	
	
	 // queue for use from game logic to display
	init_queue(&Direction, 1); // only one thing so could make it a semeaphore
	init_queue(&Locations, 2);
	
	Display();
	write_q(&Direction, 2); // first thing you send means nothing as it is initializing snake
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
		
	write_q(&Direction, 2); // first thing you send means nothing as it is initializing snake
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	
	/*
	write_q(&Direction, 2);
	game();
	Display();
	
	write_q(&Direction, 2);
	game();
	Display();
	
	write_q(&Direction, 2);
	game();
	Display();
	
	write_q(&Direction, 2);
	game();
	Display();
	*/
	
	                           //sequence for hitting 4 fruits
/*	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 1);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 1);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 3);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
		write_q(&Direction, 1);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
	write_q(&Direction, 1);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
		write_q(&Direction, 1);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
		write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
	Display();
		write_q(&Direction, 2);
	for (volatile int32_t i = 0; i < 123456; i++){}
	game();
<<<<<<< HEAD
	Display();  */

	
while(1){
		knob();
		game();
		Display();
}
		
	/*
	write_q(&Direction, 2);
	write_q(&Locations, 23); // once dispaly can read we can test its entire functionality with dummy data
	write_q(&Locations, 147); // game will use the value to print +96 when printing 2 squares - for init game
	
	Display(); // not sure about the warning 
	
	write_q(&Locations, 71); // first write is to draw
	write_q(&Locations, 51); // second write is to clear
	
	Display();*/
	
	//init_queue(&light, 1);
	//write_q(&light, 400);
	
	//led();
	

	
	
	//TODO: knob queue
	//TODO: LED queue
	//TODO: Game queue
	
	
}