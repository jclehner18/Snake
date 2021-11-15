
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


// initializes the gpio used for the display -> init_gpio();
void init_gpio(void); 

// initializes the spi for use in the display -> init_spi();
void init_spi(void);

// sets the reset line for s period of time as needed for display initialization -> reset();    
void reset(void); // reset line not display reset

// sends the required data via spi to initialize the display -> init_display();
void init_display(void); 

// sends the value it is given via spi -> send_packet(unt32_t packet);
void send_packet(uint16_t packet); 

// sets CD line low for convinience purposes -> CDLow();
void CDLow(void); 

// same as CDLow but set high -> CDHigh();
void CDHigh(void); 

// clears everything on the display -> clear_all();
void clear_all(void);

// resets the current column address MSB and LSB to 0 -> column_reset();
void column_reset(void); 

// sets the page, takes an int from 1-8 -> set_page(int32_t x);
void set_page (uint16_t x); 

// takes the row position of where to draw the square from 1-12 and draws the square in that spot -> set_square(uint32_t x);
void set_square(uint16_t x); 

// same as set_square but writes 0x00 to clear -> clear_square(uint32_t x);
void clear_square(uint16_t x); 

// takes board position int 1-96 and draw a square to the corrosponding spot -> DrawSquare(intBoardPosition);
void DrawSquare(int16_t BoardPosition);

// same as Draw Square but clears given boardposition -> ClearSquare(intBoardPosition);
void ClearSquare(int16_t BoardPosition);

// simple display sequence to be played on game over -> gameoveranimation();
void gameoveranimation(void);

// actual display fuction, runs all of above -> Display();
void Display(void);

