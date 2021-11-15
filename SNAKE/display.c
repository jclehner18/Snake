// display task rework by Josiah Mortorff
// Reworked version 11/7/21
// This task will read 2 inputs from a queue and display them to the display, it will read one square to display and one square to clear


#include "display.h"
#include "main.h"

static bool Isinitialized =false; // used to keep track of if the display has been initiailized


void init_gpio(void)
{
RCC->IOPENR |= RCC_IOPENR_GPIOAEN; 
GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk); 
GPIOA->MODER |= 1 << GPIO_MODER_MODE4_Pos; // PA4 to output
GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk); 
GPIOA->MODER |= 2 << GPIO_MODER_MODE5_Pos; // PA5 to Alternate Function 
GPIOA->MODER &= ~(GPIO_MODER_MODE7_Msk); 
GPIOA->MODER |= 2 << GPIO_MODER_MODE7_Pos; // PA7 to alternate function 
GPIOA->MODER &= ~(GPIO_MODER_MODE1_Msk); 
GPIOA->MODER |= 1 << GPIO_MODER_MODE1_Pos ; // PA1 to output 
GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk); 
GPIOA->MODER |= 1<< GPIO_MODER_MODE0_Pos; // PA0 to output 
}

void init_spi(void)
{

// SPI seemed to be cause of some column issues, when rewritting the code 
//some other groups spi initialization from the display lab was referenced for trouble shooting

RCC->APB2ENR |= (1U << RCC_APB2ENR_SPI1EN_Pos);
SPI1->CR1 |= (1U << SPI_CR1_CPHA_Pos);
SPI1->CR1 |= (1U << SPI_CR1_CPOL_Pos);
SPI1->CR1 |= (1U << SPI_CR1_MSTR_Pos); // Master Configuration
SPI1->CR1 |= (1U << SPI_CR1_SSI_Pos); 
SPI1->CR1 |= (1U << SPI_CR1_SSM_Pos) ; 
SPI1->CR1 |= (3U << SPI_CR1_BR_Pos); // fPCLK/16
SPI1->CR1 |= (SPI_CR1_SPE); // Peripheral enabled
}

void reset(void) 
{ 
GPIOA->ODR |= (1U << 0); // PA0 is the reset line, originally wasted way more time than needed here so it was reduced
for( volatile int16_t n =0; n<8; n++){} // delay loop to give the line enough time high / low
GPIOA->ODR &= ~(1U << 0);
for( volatile int16_t n =0; n<16; n++){}
GPIOA->ODR |= (1U <<0);
for( volatile int16_t n =0; n<8; n++){}
}

void init_display(void)
{
send_packet(0x40);
send_packet(0xA1);
send_packet(0xC0);
send_packet(0xA4);
send_packet(0xA6);
send_packet(0xA2);
send_packet(0x2F);
send_packet(0x27);
send_packet(0x81);
send_packet(0x10); // not sending FA and 90, aren't needed for our purposes
send_packet(0xAF);
}

void send_packet(uint16_t packet)
{
GPIOA->ODR &= ~(1U << 4); // CSO
SPI1->DR = packet;
for( volatile int16_t n =0; n<5; n++){}
while( SPI1->SR & SPI_SR_BSY) {} //loop until SPI completed.  Not sure if this is a busy wait will need to verify its allowed ------------------------------------------------------------
GPIOA->ODR |= (1U << 4);
}

void CDLow (void) // a function is easier than remembering which ouput is the CD line
{
GPIOA->ODR &= ~(1U << 1);// Sets PA1 low
}

void CDHigh (void)
{
GPIOA->ODR |=(1U << 1);
}


void clear_all(void)
{
	for(int16_t m=1; m<9; m++) // loops through each page
	{
		set_page(m);
		for (int16_t m=0; m<102; m++)// size of 102 because display is 102 long
			{send_packet(0x00);} // value send is hex 0x00 = none 0xFF = all
	}
}

void column_reset(void) // resets the column position to the start of the page
{
CDLow(); // cd set low to send commands
send_packet(0x00); // LSB to 0
send_packet(0x10); // MSB to 0
CDHigh();
}


void set_page(uint16_t page) // takes int value 1-8 and will set the corrosponding page
	{ 
		CDLow();// CD low to write commands
		int page_0 = 176; // 176 = B0 which is the command for the first page position
		int newpage = page_0+(page-1); // page - 1 because page 1 is = page 0 but 1 makes more sense
		send_packet(newpage);
		column_reset();// resets the columns on page change
		CDHigh();
	}


void set_square(uint16_t x){ // takes a int from 1-12 and draws a square in that spot (we are only displaying in an 8x12 grid)
CDLow(); // command mode
if(x==1){send_packet(0x10); send_packet(0x00);} 
else if(x==2){send_packet(0x08); } // LSB of 8 is just 8 pixels or 1 square over
else if(x==3){send_packet(0x11); }
else if(x==4){send_packet(0x11); send_packet(0x08); }
else if(x==5){send_packet(0x12); }
else if(x==6){send_packet(0x12); send_packet(0x08); }
else if(x==7){send_packet(0x13); }
else if(x==8){send_packet(0x13); send_packet(0x08); }
else if(x==9){send_packet(0x14); }
else if(x==10){send_packet(0x14); send_packet(0x08); }
else if(x==11){send_packet(0x15); }
else if(x==12){send_packet(0x15); send_packet(0x08); }
CDHigh();
for(int16_t m=0; m<8; m++) // for fanicier displays this could easily be changed
{
send_packet(0xFF); // solid square
}
column_reset();
}


void clear_square(uint16_t x){ // same functionality as draw square but it will send 0x00 8 times to the display
CDLow(); 
if(x==1){send_packet(0x10); send_packet(0x00);}
else if(x==2){send_packet(0x08); }
else if(x==3){send_packet(0x11); }
else if(x==4){send_packet(0x11); send_packet(0x08); }
else if(x==5){send_packet(0x12); }
else if(x==6){send_packet(0x12); send_packet(0x08); }
else if(x==7){send_packet(0x13); }
else if(x==8){send_packet(0x13); send_packet(0x08); }
else if(x==9){send_packet(0x14); }
else if(x==10){send_packet(0x14); send_packet(0x08); }
else if(x==11){send_packet(0x15); }
else if(x==12){send_packet(0x15); send_packet(0x08); }
CDHigh();
for(int16_t m=0; m<8; m++)
{
send_packet(0x00);
}
column_reset();
}

void DrawSquare(int16_t BoardPosition){ // takes the board position 0-96 and converts it to corresponding page and column
	int16_t column = (BoardPosition % 12); // sets the column as the remainder after a division by 12
	int16_t page = (BoardPosition / 12.01)+1; // the 0.01 is for end values 12/12=1 but it is still page 1  // +1 because set page accepts values 1-8 not 0
	if (column==0){column=12;} // for instances with no remainder 96%12=0 which will always be column 12
	set_page(page);
	set_square(column);
}

void ClearSquare(int16_t BoardPosition){ // same as DrawSquare but clears the position
	int16_t column = (BoardPosition % 12); // sets the column as the remainder after a division by 12
	int16_t page = (BoardPosition / 12.01)+1; // the 0.01 is for end values 12/12=1 but it is still page 1  // +1 because set page accepts values 1-8 not 0
	if (column==0){column=12;} // for instances with no remainder 96%12=0 which will always be column 12
	set_page(page);
	clear_square(column);
}

void gameoveranimation(){ // simple animation to play on gameover, alse serves to clear leftover pieces being displayed
	for (volatile int16_t i = 1; i <= 12; i++) // runs 12 times, once for each column
	{
		for (volatile int32_t i = 0; i < 123456; i++){} // delay to show the animation so its not instant
		DrawSquare(i); // draws a vertical bar corresponding with i = column position
		DrawSquare(i+12);
		DrawSquare(i+24);
		DrawSquare(i+36);
		DrawSquare(i+48);
		DrawSquare(i+60);
		DrawSquare(i+72);
		DrawSquare(i+84);
			
		ClearSquare(i+12-1); // clears the previous vertical bar
		ClearSquare(i+24-1);
		ClearSquare(i+36-1);
		ClearSquare(i+48-1);
		ClearSquare(i+60-1);
		ClearSquare(i+72-1);
		ClearSquare(i+84-1);
		ClearSquare(i-1);
			
			if(i==12){ // clears the lines once it reaches the end
				for (volatile int32_t i = 0; i < 123456; i++){}
				ClearSquare(i+12);
				ClearSquare(i+24);
				ClearSquare(i+36);
				ClearSquare(i+48);
				ClearSquare(i+60);
				ClearSquare(i+72);
				ClearSquare(i+84);
				ClearSquare(i);
			}
	}
}

void victoryanimation(){
	clear_all();
	DrawSquare(16); DrawSquare(17); DrawSquare(18); DrawSquare(19); DrawSquare(20); DrawSquare(21); // drawing a trophie,general shape shown via indents
	DrawSquare(28); DrawSquare(29); DrawSquare(30); DrawSquare(31); DrawSquare(32); DrawSquare(33);
									DrawSquare(41); DrawSquare(42); DrawSquare(43); DrawSquare(44);
																	DrawSquare(54); DrawSquare(55);
																	DrawSquare(66); DrawSquare(67);
									DrawSquare(77); DrawSquare(78); DrawSquare(79); DrawSquare(80);
	for (volatile int16_t i = 1; i <= 12; i++) // runs micro animation 12 times
	{
		int rem1 = i % 2;
    if (rem1 == 0) // checks if num = even or odd and alternates based off that
		{
			for (volatile int32_t i = 0; i < 123456; i++){} // draws alternating pixels on side of display to give the animation some motion
			ClearSquare(2); ClearSquare(12);
			ClearSquare(13); ClearSquare(23);
			ClearSquare(26); ClearSquare(36);
			ClearSquare(37); ClearSquare(47);
			ClearSquare(50); ClearSquare(60);
			ClearSquare(61); ClearSquare(71);
			ClearSquare(74); ClearSquare(84);
			ClearSquare(85); ClearSquare(95);	
			
			DrawSquare(1); DrawSquare(11);
			DrawSquare(14); DrawSquare(24);
			DrawSquare(25); DrawSquare(35);
			DrawSquare(38); DrawSquare(48);
			DrawSquare(49); DrawSquare(59);
			DrawSquare(62); DrawSquare(72);
			DrawSquare(73); DrawSquare(83);
			DrawSquare(86); DrawSquare(96);
		}
		else
		{
			for (volatile int32_t i = 0; i < 123456; i++){} // delay loop is to give time for animation to actually show
			ClearSquare(1); ClearSquare(11);
			ClearSquare(14); ClearSquare(24);
			ClearSquare(25); ClearSquare(35);
			ClearSquare(38); ClearSquare(48);
			ClearSquare(49); ClearSquare(59);
			ClearSquare(62); ClearSquare(72);
			ClearSquare(73); ClearSquare(83);
			ClearSquare(86); ClearSquare(96);
			
			DrawSquare(2); DrawSquare(12);
			DrawSquare(13); DrawSquare(23);
			DrawSquare(26); DrawSquare(36);
			DrawSquare(37); DrawSquare(47);
			DrawSquare(50); DrawSquare(60);
			DrawSquare(61); DrawSquare(71);
			DrawSquare(74); DrawSquare(84);
			DrawSquare(85); DrawSquare(95);
		}
			
	}
	clear_all();// clears animation when finished
}


void Display()
{
if (Isinitialized==false){ // runs through all the required startup procedures, uses bool condition to only do this the first time display is used
init_gpio(); 
CDLow();
init_spi() ;
reset();
init_display();
CDHigh();
clear_all();
Isinitialized=true;
}
else{
	// will be reading 2 values from a queue, a draw square and a clear square, there are instances display will handle
	// Standard move: Draw new head and clear old head
	// Initalization: Draw head and draw new fruit
	
	int16_t msg; // the first message written / message to be drawn
	int16_t msg2; //second message / message to be cleared
	read_q(&Locations, &msg);  
	read_q(&Locations, &msg2);
	
	if(msg==123 && msg2==123) // the game will send these 2 values on game over, their value is arbitrary as long as its not two values that would normally be used
		{
			gameoveranimation();
		} 
	else if(msg==124 && msg2==124) // the game will send these 2 values on game over, their value is arbitrary as long as its not two values that would normally be used
		{
			victoryanimation();
		} 
	else{
			ClearSquare(msg2);
		
			if(msg2>96) // there is one instance where 2 squares must be drawn, on game start. to accomodate this any message > 96 for msg2 will also be drawn
					{
						msg2=msg2-96; // if 2 things need drawn the placedment desired + 96 is received
						DrawSquare(msg2);
					}
			else{
				DrawSquare(msg);
					}
			}
	}


}