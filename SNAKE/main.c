// main file for running the schedule


//HARDWARE REQUIREMENTS
//stm32l053R8 Microcontroller
//breadboard
//EA DOGS102N-6 Display - x3 1uF Capacitors
//PEC12R - 12mm Incremental Encoder - x2 10k Ohm Resistors - x2 0.01uF Capacitors
//LED - 330 Ohm Resistor

//WIRING

#include "main.h"
queue_t Direction;// queue for use from knob to game logic
queue_t Locations;
queue_t light;

int main()
{
	//queues for game logic to display
	init_queue(&Direction, 1);
	init_queue(&Locations, 2);
	//queue for game to led
	init_queue(&light, 1);
	
	while(1)
	{
		knob();
		game();
		led();
		Display();
	}
}