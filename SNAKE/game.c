// -	For the actual game logic. It will accept the user input (CW or CCW) and keep track of the game status. It will produce an output of snake location as well as a status output.

//  game board is 8 x 12 places, each row consists of 12 places (columns) with 8 rows (pages) total
// alternate mode to tracking positions is with [xpos, ypos] where each position requires 2 datapieces to make up its location an x and a y cord
//still need to move stuff into header file, ect.

//#include <stdio.h>
//#include <stdlib.h>
//#include "stm32l053xx.h"
//#include <stdbool.h>
//#include <stdint.h>

//#include <stdio.h>
//#inlcude <stdint.h>
//#include <stdbool.h>

#include "game.h"
#include "main.h"



static int head;
static int futurehead;
static int fruitposition;

static bool fruitcollision;
static bool gamestart=true;
static int snakedirection;
static int length=1;
static int snakepositions[20];




//------------------------------------------------------------------------------------------------------------------------------------------------------------
void appendsnake( bool fruitcollision) // updating the snakepositions array with new head position
{
if (fruitcollision==true)
    {
    length++;
    void generatenewfruit();
    snakepositions[length-1]=futurehead; // if a fruit is achieved the snake grows 1 spot so all values for position will remain the same but one new spot will be added to the array
    }

else{
    for(int i=0; i<length; i++)
    {                                                                    
    snakepositions[i]=snakepositions[i+1]; // shifts all positions, will erase the oldest loc
    }
snakepositions[length-1]=futurehead; //adds in the new postion to the head spot
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void initializesnake(){ // will run at the start of game, set the snake positions array to set starting point

head = 49; // general middle left side of screen to give player time to react
snakedirection = 2;
int snakepositions[20]={0}; // sets array of positions to all 0

futurehead=49;
appendsnake( false);
int fruit = 153; // starting fruit will always be the same, in straight line away from start
fruitposition=57;
write_q(&Locations, 49); // doesnt draw the first square -- stops the random square in the corner
write_q(&Locations, fruit);
gamestart=false;
}


//---------------------------------------------------------------------------------------------------------------------------------------------
bool valueinarray(int array[], int search, int size)// used in check boundcollision, checks if a given value is in a gven array
{                                                   // couldnt seem to get this to work y checking size of array so im passing parameter size too
bool isinarray=false;
for (int i=0; i<size; i++)
{if(array[i]==search){isinarray=true; break;}}
return isinarray;
}


//--------------------------------------------------------------------------------------------------------------------------------------------

bool checkfruitcollision(int futurehead){
bool fruitcollision = false;
if(futurehead==fruitposition)
{
fruitcollision = true;
}
return fruitcollision;
}

//--------------------------------------------------------------------------------------------------------------------------------
void generatenewfruit()  // generates a new fruit location using random num, also verifies the new fruit is not placed within the snake
{
fruitposition = fruitposition+25;
if(fruitposition>96){fruitposition=fruitposition-96;}
       
while(valueinarray(snakepositions, fruitposition, 20)==true){ //looked at generating within a range excluding some numbers but couldnt get anything to work
fruitposition = fruitposition+20;                        // this will loop until a number is generated the meets criteria, very non-optimal will fix later
if(fruitposition>96){fruitposition=fruitposition/96;}
}
}

//-----------------------------------------------------------------------------------------------------------------------------------------



int updatedirection(int msg){ // determines the direction the snake is moving after the input (N=1, E=2, S=3, W=4)
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

//-----------------------------------------------------------------------------------------------------------------------------------------------------

int future(int newdirection) // defines the next position of the snakes head
{
if (newdirection ==1){ futurehead=head-12;} //game is 8x12 squares, A north move is simply position - 12
else if(newdirection ==2){ futurehead=head+1;}
else if(newdirection ==3){ futurehead=head+12;}
else if(newdirection ==4){ futurehead=head-1;}
return futurehead;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
bool checkboundcollision(int newdirection) //checks if the next position will hit any of the four walls
{                                                        // as far as I can tell you cant return more than 1 parameter from fucntion without statically allocating mem
                                                         // otherwise future and check bound collision can be combined
int leftbound[8]={1,13,25,37,49,61,73,85}; //the 8 leftmost grid positions
int rightbound[8]={12,24,36,48,60,72,84,96};
bool hitbound=false;
bool rightbord=valueinarray(rightbound,head, 8);
bool leftbord=valueinarray(leftbound,head, 8);
if(newdirection==2 && rightbord==true){ hitbound=true;}
else if (newdirection==4 && leftbord==true){ hitbound=true;}
if(futurehead<1 || futurehead>96){hitbound=true;}
return hitbound;

}

//----------------------------------------------------------------------------------------------------------------------------------------
bool checkbodycollision(){
bool collision = false;
if(valueinarray(snakepositions, futurehead, 20)==true)
{
collision = true;
}
return collision;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
int game(){
   
    int newdirection;
    int msg_send1;
    int msg_send2;
   
    int16_t msg; //variable from queue to be used,
		read_q(&Direction, &msg); // will be CWW,straight,or CW (1, 2, 3)
   
    if(gamestart==true)
        {
        initializesnake();
        }
       
    else{
       
        newdirection = updatedirection(msg);
        futurehead=future(newdirection);
       
        if(checkboundcollision(newdirection)==true || checkbodycollision()==true)
            {
                write_q(&Locations, 123);
                write_q(&Locations, 123);
            }
        else{
                write_q(&Locations, head);
                if(checkfruitcollision(futurehead)==true) //if it hits a fruit clear nothing
                    { 
										generatenewfruit();  // running this line makes it successfully generate the new fruit but it then still elaves the old fruit position in place
										write_q(&Locations, fruitposition+96);
										}
                else
                    {
										write_q(&Locations, snakepositions[0]);
										} // else clear oldest value before its appended
                   
               
                appendsnake( checkfruitcollision(futurehead));
                head = futurehead;
                snakedirection=newdirection;
            }
         
    }
   
   
   
   
   
   
}