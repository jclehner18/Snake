// -	For the actual game logic. It will accept the user input (CW or CCW) and keep track of the game status. It will produce an output of snake location as well as a status output.

//  game board is 8 x 12 places, each row consists of 12 places (columns) with 8 rows (pages) total
// alternate mode to tracking positions is with [xpos, ypos] where each position requires 2 datapieces to make up its location an x and a y cord
//still need to move stuff into header file, ect.

#include <stdio.h>
#include <stdlib.h>
#include "stm32l053xx.h"
#include <stdbool.h>
#include <stdint.h>

int head;
int futurehead;

static int snakedirection; // not 100% sure im allowed to declare local var static?
                           // int from 1-4, N, E, S, W



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


bool valueinarray(int array[8], int search)// used in check boundcollision, checks if a given value is in a gven array
{
	bool isinarray=false;
	for (int i=0; i<5; i++)
	{if(array[i]==search){isinarray=true; break;}} 
	return isinarray;
}

 
bool checkboundcollision(newdirection, head, futurehead) //checks if the next position will hit any of the four walls
{                                                        // as far as I can tell you cant return more than 1 parameter from fucntion without statically allocating mem
                                                         // otherwise future and check bound collision can be combined
	int leftbound[8]={1,13,25,37,49,61,73,85}; //the 8 leftmost grid positions
	int rightbound[8]={12,24,36,48,60,72,84,96};
	bool hitbound=false;
	bool rightbord=valueinarray(rightbound,head);
	bool leftbord=valueinarray(leftbound,head);
	
	if(newdirection==2 && rightbord==true){ hitbound=true;}//if going right and on right border
	else if (newdirection==4 && leftbord==true){ hitbound=true;}
	if(futurehead<1 || futurehead>96){hitbound=true;} //outside the north and south bounds
	return hitbound;
}

void game(){ 
	
		int16_t msg; //variable from queue to be used, 
								// will be CWW,straight,or CW (1, 2, 3)
		
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
		
		
	
	
	
	

	}