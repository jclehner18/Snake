
#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>

int updatedirection(int msg);
int future(int newdirection, int head);
bool valueinarray(int array[], int search, int size);
bool checkboundcollision(int newdirection, int head, int futurehead);
int generatenewfruit(void);
bool checkbodycollision(int futurehead);
bool checkfruitcollision(int futurehead);
void appendsnake(int futurehead, bool fruitcollision, int length);
int calcsnakelength(void);
void initializesnake(void);
void game(void);