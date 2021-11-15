
/* Copyright 2021 John Lehner & Josiah Mortorff

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


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
