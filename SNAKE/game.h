
#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>


// shifts or adds values in snake array based on direction and collission -> appendsnake(bool fruit collision);
void appendsnake( bool fruitcollision);

// sets starting conditions for game, used on game restart -> initializesnake();
void initializesnake();

// checks if a value is in a given array -> valueinarray(int array, int16_t search, int16_t size);
bool valueinarray(int array[], int16_t search, int16_t size);

// checks if futurehead == fruitposition -> checkfruitcollision(int16_t futurehead);
bool checkfruitcollision(int16_t futurehead);

// generates new fruit in valid position -> generatenewfruit();
void generatenewfruit();

// updates snakedirection based on message from queue -> updatedirection(int16_t msg);
int updatedirection(int16_t msg);

// updates future head based on the new direction -> future(int16_t newdirection);
int future(int16_t newdirection);

// checks if futurehead will collide out of bounds -> checkboundcollision(int16_t newdirection);
bool checkboundcollision(int16_t newdirection);

// checks if futurehead will hit a body segment -> checkbodycollision();
bool checkbodycollision();

// main function to be called for game
void game(void);
