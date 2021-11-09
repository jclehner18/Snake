#include "stm32l053xx.h"
#include <stdint.h>
#include <stdbool.h>

void init_gpio(void); 
void init_spi(void);
void reset(void); // for the reset line not to reset the display
void init_display(void); // sends the required data to initialize the display
void send_packet(uint32_t); // will send whatever it is given
void CDLow(void); // set CD line low - for commands   // this was earier than remembering what pin was CD
void CDHigh(void); // set CD line high - for actually writing
void clear_all(void); // clears eveything on the display
void column_reset(void); // sets the column MSB and LSB to start
void set_page (uint32_t x); // sets the page, takes an int from 1-8
void set_square(uint32_t x); // takes the row position of where to draw the square from 1-12 and draws the square in that spot
void clear_square(uint32_t x); // same as set_square but writes 0x00 to clear
void DrawSquare(int BoardPosition); // will accept the board position int 1-96 and draw a square to the corrosponding spot
void ClearSquare(int BoardPosition); // same as Draw Square but clears given boardposition
void gameoveranimation(void);

void Display(void);