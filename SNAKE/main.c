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
	
	Display();
	write_q(&Direction, 3);
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
	write_q(&Direction, 2);
	game();
	Display();
	write_q(&Direction, 2);
	game();
	Display();
	write_q(&Direction, 3);
	game();
	Display();
	write_q(&Direction, 2);
	game();
	Display();
	write_q(&Direction, 2);
	game();
	Display();
	write_q(&Direction, 1);
	game();
	Display();
	write_q(&Direction, 1);
	game();
	Display();
	write_q(&Direction, 2); //original fruit doesnt disappear and it is recognized as part of the snake. once fruit is hit, the other square is the new snake, nothing gets appended
	game();
	Display();
	write_q(&Direction, 2);
	game();
	Display();
	
	/*
	write_q(&Direction, 2);
	write_q(&Locations, 23); // once dispaly can read we can test its entire functionality with dummy data
	write_q(&Locations, 147); // game will use the value to print +96 when printing 2 squares - for init game
	
	Display(); // not sure about the warning 
	
	write_q(&Locations, 71); // first write is to draw
	write_q(&Locations, 51); // second write is to clear
	
	Display();*/
	
	init_queue(&light, 1);
	write_q(&light, 400);
	
	led();
	
	//init_queue(&knob_action, 1);
	//write_q(&light, update_btn(&quad_A)); //cant pass quad_a
	
	//TODO: knob queue
	//TODO: LED queue
	//TODO: Game queue
	
	
}