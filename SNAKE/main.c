// main file for running the schedule

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


#include "display.c" //fixes Display() warning, not sure if this is misra compliant though






int main()
{
	queue_t Direction;// queue for use from knob to game logic
	queue_t Locations; // queue for use from game logic to display
	init_queue(&Direction, 1); // only one thing so could make it a semeaphore
	init_queue(&Locations, 2);
	
	write_q(&Locations, 39); // once dispaly can read we can test its entire functionality with dummy data
	write_q(&Locations, 40);
	
	Display(); // not sure about the warning 
	
	
	
	
}