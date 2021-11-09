// main file for running the schedule

#include "main.h"


queue_t Direction;// queue for use from knob to game logic
queue_t Locations;

queue_t light;

 //fixes Display() warning, not sure if this is misra compliant though




//knob timing


int main()
{
	 // queue for use from game logic to display
	init_queue(&Direction, 1); // only one thing so could make it a semeaphore
	init_queue(&Locations, 2);
	
	write_q(&Locations, 1); // once dispaly can read we can test its entire functionality with dummy data
	write_q(&Locations, 2);
	
	Display(); // not sure about the warning 
	
	
	init_queue(&light, 1);
	write_q(&light, GPIOC->BSRR = GPIO_BSRR_BS_0);
	
	led();
	
	//TODO: knob queue
	//TODO: LED queue
	//TODO: Game queue
	
	
	
	
}