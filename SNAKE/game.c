// -	For the actual game logic. It will accept the user input (CW or CCW) and keep track of the game status. It will produce an output of snake location as well as a status output.

//  game board is 8 x 12 places, each row consists of 12 places (columns) with 8 rows (pages) total
// alternate mode to tracking positions is with [xpos, ypos] where each position requires 2 datapieces to make up its location an x and a y cord
//still need to move stuff into header file, ect.

//#include <stdio.h>
//#include <stdlib.h>
//#include "stm32l053xx.h"
//#include <stdbool.h>
//#include <stdint.h>

#include "game.h"
#include "main.h"


static int head;
static int futurehead;
static int snakedirection; // not 100% sure im allowed to declare local var static?
                           // int from 1-4, N, E, S, W
static int snakepositions[20]; //  snakepositions[0] is the tail, the head is the furthest current value out, this should work havnt tested yet
static int fruitposition;
static bool gamestart=true;



int updatedirection(msg){ // determines the direction the snake is moving after the input (N=1, E=2, S=3, W=4)
	int newdirection;
	if (snakedirection==1)
		{
		if(msg==1){newdirection=4;}//going N, turn CWW = W
		else if(msg==2){newdirection=1;} //going N, straight = N
		else if(msg==3){newdirection=2;} //going N, turn CW = E
		else{}// should never be anything but 1, 2, 3
		}
	else if (snakedirection==2)
		{
		if(msg==1){newdirection=1;}//going N, turn CWW = W
		else if(msg==2){newdirection=2;}
		else if(msg==3){newdirection=3;}
		else{}// should never be anything but 1, 2, 3
		}
	else if (snakedirection==3)
		{
		if(msg==1){newdirection=2;}//going N, turn CWW = W
		else if(msg==2){newdirection=3;}
		else if(msg==3){newdirection=4;}
		else{}// should never be anything but 1, 2, 3
		}
	else if (snakedirection==4)
		{
		if(msg==1){newdirection=3;}//going N, turn CWW = W
		else if(msg==2){newdirection=4;}
		else if(msg==3){newdirection=1;}
		else{}// should never be anything but 1, 2, 3
		}
		return newdirection;
}



int future(newdirection, head) // defines the next position of the snakes head
{
	if (newdirection ==1){ futurehead=head-12;} //game is 8x12 squares, A north move is simply position - 12
	else if(newdirection ==2){ futurehead=head+1;}
	else if(newdirection ==3){ futurehead=head+12;}
	else if(newdirection ==4){ futurehead=head-1;}
	return futurehead;
}


bool valueinarray(int array[], int search, int size)// used in check boundcollision, checks if a given value is in a gven array
{                                                   // couldnt seem to get this to work y checking size of array so im passing parameter size too
	bool isinarray=false;
	for (int i=0; i<size; i++)
	{if(array[i]==search){isinarray=true; break;}} 
	return isinarray;
}


bool checkboundcollision(newdirection, head, futurehead) //checks if the next position will hit any of the four walls
{                                                        // as far as I can tell you cant return more than 1 parameter from fucntion without statically allocating mem
                                                         // otherwise future and check bound collision can be combined
	int leftbound[8]={1,13,25,37,49,61,73,85}; //the 8 leftmost grid positions
	int rightbound[8]={12,24,36,48,60,72,84,96};
	bool hitbound=false;
	bool rightbord=valueinarray(rightbound,head, 8);
	bool leftbord=valueinarray(leftbound,head, 8);
	
	if(newdirection==2 && rightbord==true){ hitbound=true;}//if going right and on right border
	else if (newdirection==4 && leftbord==true){ hitbound=true;}
	if(futurehead<1 || futurehead>96){hitbound=true;} //outside the north and south bounds
	return hitbound;
}

int generatenewfruit()  // generates a new fruit location using random num, also verifies the new fruit is not placed within the snake
{
	int fruitposition;
	
	int lower = 1, upper = 96;
	
	//fruitposition = (rand() % (upper - lower + 1)) + lower; rand() isnt actually rand as cant use srand(time()) to set random seed
	fruitposition = fruitposition+15;
	if(fruitposition>96){fruitposition=fruitposition/96;}
        //printf("%d ", fruitposition); // from testing in an online compiler
	while(valueinarray(snakepositions, fruitposition, 20)==true){ //looked at generating within a range excluding some numbers but couldnt get anything to work
		//fruitposition = (rand() % (upper - lower + 1)) + lower;     // this will loop until a number is generated the meets criteria, very non-optimal will fix later
		fruitposition = fruitposition+15;
		if(fruitposition>96){fruitposition=fruitposition/96;}
        
	}
	fruitposition = fruitposition+96;// display knows that a number this big should be displayed not cleared
	return fruitposition;
}

bool checkbodycollision(int futurehead){
	bool collision = false;
	if(valueinarray(snakepositions, futurehead, 20)){
		collision = true;
	}
	return collision;
}

bool checkfruitcollision(int futurehead){
	bool fruitcollision = false;
	if(futurehead==fruitposition){
		fruitcollision = true;
	}
	return fruitcollision;
}

void appendsnake(int futurehead, bool fruitcollision, int length){ // updating the snakepositions array with new head position
	if (fruitcollision==true){
			snakepositions[length]=futurehead; // if a fruit is achieved the snake grows 1 spot so all values for position will remain the same but one new spot will be added to the array
	}
	else{
		for(int i; i<length-1; i++){ //potential problem when size = 19 trying to check value i+1 that is out of the array
			snakepositions[i]=snakepositions[i+1]; // shifts all positions, will erase the oldest loc
		}
		snakepositions[length]=futurehead; //adds in the new postion to the head spot
	}
}

// [5,6,7,0,0,0]  idea behind shifting= oldest tail no longer exists when no fruit was gotten
// [6,7,0,0,0,0]  the shift gets rid of where head was as its set to the position one past which is 0
// [6,7,8,0,0,0]  resets the head position to future head




int calcsnakelength(){ // should go through array and figure out lenght of snake, snake will not take up all 20 positions of the array rather thsi will calc # of array positions used
	int length=0;
	for(int i; i<20; i++){
		if(snakepositions[i]!=0){length++;}
		else{break;} // this should break out of the for loop but need to test it still
	}
	return length;
}



void initializesnake(){ // will run at the start of game, set the snake positions array to set starting point
	head = 50; // general middle left side of screen to give player time to react
	snakedirection = 2;
	int snakepositions[20]={0}; // sets array of positions to all 0
	appendsnake(50, false, 0); // adds the single head to the snake positions
	calcsnakelength(); // recalcualtes snake length
	int fruit = 153; // starting fruit will always be the same, in straight line away from start
	write_q(&Locations, snakepositions[0]);
	write_q(&Locations, fruit);
	gamestart=false;
}

void game(){ 
	
		int16_t msg; //variable from queue to be used, 
		read_q(&Direction, &msg); // will be CWW,straight,or CW (1, 2, 3)
		
		/*   dummy queue code, queues not implemented yet but this is the general section to read from it, read should never fail as game requires a new input to run
    bool successful_read = false;
    for (int i = 1; i<15; i++){
    successful_read = read_q(&q1, &msg);
		
				if (successful_read){
            printf("Successful access attempt #%d for q1 ", i);
            printf("found = %d.\n", msg);
        }else{
            printf("Access %d found %d, which is a dummy!\n",i, msg);
        }
		}
		*/
	
	//-----------------------------------------------TODO----------------------------------------------------------
	
		if(gamestart==true){ initializesnake();}
		else{
			bool collision=false;
			
			int newdirection = updatedirection(msg); // new direction absed on input from queue
			futurehead = future(newdirection, head); // new head position based on new dir and old head
			//if (checkboundcollision(newdirection, head, futurehead)==true || checkbodycollision(futurehead)==true)
			//	{ // checks if either type of collision has occured
				//	collision=true;
				//	write_q(&Locations, 0); // display task knows that 2 0's means game over
				//	write_q(&Locations, 0);
			//	} 
			//else{
				appendsnake(futurehead, checkfruitcollision(futurehead), calcsnakelength()); // assuming function calls can be within a fucntion call
				head = futurehead;
				snakedirection = newdirection;
				write_q(&Locations, futurehead);
				write_q(&Locations, snakepositions[0]);
			//}
			
			
			
			
		}
	
		
		
		
	
	
	
	

	}