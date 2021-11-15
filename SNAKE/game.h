
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
