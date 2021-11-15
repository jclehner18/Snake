
#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>


void appendsnake( bool fruitcollision);
void initializesnake();
bool valueinarray(int array[], int16_t search, int16_t size);
bool checkfruitcollision(int16_t futurehead);
void generatenewfruit();
int updatedirection(int16_t msg);
int future(int16_t newdirection);
bool checkboundcollision(int16_t newdirection);
bool checkbodycollision();

void game(void);
