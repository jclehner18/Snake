// main file for running the schedule

#include "main.h"
queue_t Direction;// queue for use from knob to game logic
queue_t Locations;
queue_t light;

int main()
{
	 // queue for use from game logic to display
	init_queue(&Direction, 1); // only one thing so could make it a semeaphore
	init_queue(&Locations, 2);
	init_queue(&light, 1);
	
while(1){

		knob();
		game();
		led();
		Display();
}
}