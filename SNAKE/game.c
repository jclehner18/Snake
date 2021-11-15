// -	For the actual game logic. It will read input via queue (CW or CCW) and keep track of the game status. It will produce an output a value to draw and clear via queues.

//  game board is 8 x 12 places, each row consists of 12 places (columns) with 8 rows (pages) total
//  each position is tracked with int -> 12x8 = 96 so every place gets a value

#include "game.h"
#include "main.h"



static int16_t head; //keeps track of the position of the snakes head
static int16_t futurehead; // the position of the next snake head
static int16_t fruitposition; // the position of the current fruit
static int16_t snakedirection; // int for direction snake is moving N E S W -> 1 2 3 4
static int16_t length=1; // value for tracking the length of the snake

static bool fruitcollision; // bool for if the snake collided with the fruit
static bool gamestart=true; // bool for if the game is starting

static int snakepositions[20]; // array of current snake positions




//------------------------------------------------------------------------------------------------------------------------------------------------------------
void appendsnake( bool fruitcollision) // updates the snakepositions array with new head position
{
	if (fruitcollision==true) // if a fruit is hit a different append will be made
			{
			length++; //increases length of snake as a fruit was hit
			write_q(&light, length);// led changes brightness based on length
			generatenewfruit(); // generates new fruit position
			write_q(&Locations, fruitposition+96); // second value written to queue is drawn if > 96
			snakepositions[length-1]=futurehead; // if a fruit is achieved the snake grows 1 spot so all values for position will remain the same but one new spot will be added to the array
			}

	else{
			for(int16_t i=0; i<length; i++)
			{                                                                    
			snakepositions[i]=snakepositions[i+1]; // shifts all positions, will erase the oldest loc
			}
			snakepositions[length-1]=futurehead; //adds in the new postion to the head spot
			}
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void initializesnake(){ // will run at the start of game, set the snake positions array to set starting point
	head = 49; // general middle left side of screen to give player time to react
	snakedirection = 2; // intial direction is east
	for(int16_t i=0; i<=20; i++) // reset all pos in array
	{snakepositions[i]=0;}
	//int16_t snakepositions[20]={0}; // doesnt actually set all positions to 0 like originally thought
	length=1;
	write_q(&light, 0); // resets the light to dim
	futurehead=49;
	appendsnake( false);
	int16_t fruit = 153; // starting fruit will always be the same, in straight line away from start
	fruitposition=57;
	write_q(&Locations, 49); // doesnt draw the first square -- stops the random square in the corner
	write_q(&Locations, fruit);
	gamestart=false; // sets condition to false as this only runs on game restart
}


//---------------------------------------------------------------------------------------------------------------------------------------------
bool valueinarray(int array[], int16_t search, int16_t size)// used in check boundcollision, checks if a given value is in a gven array // the array passed needs int as it it recienving array of size 20 at some point
{                                                   
	bool isinarray=false;
	for (int16_t i=0; i<size; i++) {if(array[i]==search){isinarray=true; break;}} // checks each value in the array to see if the value matches
	return isinarray;
}


//--------------------------------------------------------------------------------------------------------------------------------------------

bool checkfruitcollision(int16_t futurehead){
	bool fruitcollision = false;
	if(futurehead==fruitposition) // if the next position will hit the fruit collsion =true;
	{
		fruitcollision = true;
	}
	return fruitcollision;
}

//--------------------------------------------------------------------------------------------------------------------------------
void generatenewfruit()  // generates a new fruit location using random num, also verifies the new fruit is not placed within the snake
{
	fruitposition = fruitposition+38; // random number generation is actually quite difficult so it alwasy moves a set ammount, arbitrary value
	if(fruitposition>96){fruitposition=fruitposition-96;}
				 
	while(valueinarray(snakepositions, fruitposition, 20)==true)
		{ // checks to make sure fruit is not generated inside a currently occupied snake position.
			fruitposition = fruitposition+20;                       
			if(fruitposition>96){fruitposition=fruitposition/96;}
		}
}

//-----------------------------------------------------------------------------------------------------------------------------------------



int updatedirection(int16_t msg){ // updates the direction the snake is moving after the input (N=1, E=2, S=3, W=4)
	int16_t newdirection;
	if (snakedirection==1)
	{
	if(msg==1){newdirection=4;}//going N, turn CWW = W
	else if(msg==2){newdirection=1;} //going N, straight = N
	else if(msg==3){newdirection=2;} //going N, turn CW = E
	else{}// should never be anything but 1, 2, 3
	}
	else if (snakedirection==2)
	{
	if(msg==1){newdirection=1;}
	else if(msg==2){newdirection=2;}
	else if(msg==3){newdirection=3;}
	else{}
	}
	else if (snakedirection==3)
	{
	if(msg==1){newdirection=2;}
	else if(msg==2){newdirection=3;}
	else if(msg==3){newdirection=4;}
	else{}
	}
	else if (snakedirection==4)
	{
	if(msg==1){newdirection=3;}
	else if(msg==2){newdirection=4;}
	else if(msg==3){newdirection=1;}
	else{}
	}
	return newdirection;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

int future(int16_t newdirection) // defines the next position of the snakes head
{
	if (newdirection ==1){ futurehead=head-12;} //game is 8x12 squares, A north move is simply position - 12
	else if(newdirection ==2){ futurehead=head+1;} // going east is 1 to the right
	else if(newdirection ==3){ futurehead=head+12;} // south is +12 or one page down
	else if(newdirection ==4){ futurehead=head-1;}
	return futurehead;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
bool checkboundcollision(int16_t newdirection) //checks if the next position will hit any of the four walls
{                                                        
	int leftbound[8]={1,13,25,37,49,61,73,85}; //the 8 leftmost grid positions
	int rightbound[8]={12,24,36,48,60,72,84,96};
	bool hitbound=false;
	bool rightbord=valueinarray(rightbound,head, 8);
	bool leftbord=valueinarray(leftbound,head, 8);
	if(newdirection==2 && rightbord==true){ hitbound=true;} //if snake moving right and on the right most position = collission
	else if (newdirection==4 && leftbord==true){ hitbound=true;}
	if(futurehead<1 || futurehead>96){hitbound=true;} // checks north and south bounds
	return hitbound;

}

//----------------------------------------------------------------------------------------------------------------------------------------
bool checkbodycollision(){
	bool collision = false;
	if(valueinarray(snakepositions, futurehead, 20)==true) // if futurehead pos is already in list of snake positions
	{
	collision = true;
	}
	return collision;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
void game(void){
	
    int16_t newdirection; // the next direction based on message from queue
    int16_t msg; //variable from queue to be used,
		read_q(&Direction, &msg); // will be CWW,straight,or CW (1, 2, 3)
   
    if(gamestart==true) // checks to see if game is starting
        {
        initializesnake();
        }
       
    else{
       
        newdirection = updatedirection(msg);
        futurehead=future(newdirection);
       
        if(checkboundcollision(newdirection)==true || checkbodycollision()==true) // if either collission has happened trigger gameover condition
            {
                write_q(&Locations, 123); // display knows that these values mean gameover, values are arbitrary simply ones we werent using
                write_q(&Locations, 123);
							  gamestart=true;
            }
				else if(length>=4) // this is where the victory condition will be set, current set at 7 so its easy to demonstrate
				{
								write_q(&Locations, 124);
                write_q(&Locations, 124);
							  gamestart=true;
				}
						
        else{
               write_q(&Locations, futurehead); // write position to be drawn to queue
                if(checkfruitcollision(futurehead)==false) //if a fruit isnt hit write value to clear
                    {write_q(&Locations, snakepositions[0]);}
               
                appendsnake( checkfruitcollision(futurehead)); // append snake handles writing queue condition if a fruit is hit
                head = futurehead;
                snakedirection=newdirection; // updates static variables for next use
								
            }
    }
   
   
   
   
}