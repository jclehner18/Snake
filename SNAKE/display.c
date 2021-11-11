// display task rework by Josiah Mortorff
// Reworked version 11/7/21
// rewrote entire display code in order to solve various issues
// This task will read input from a queue and display them to the display, it will read one square to display and one square to clear

// Initialization is still all in this task it will need moved to main at some point.


#include "display.h"
#include "main.h"
static bool randomcondition=true; // used in the while loop, loop while randomcondition == true
static bool Isinitialized =false;


void init_gpio(void)
{
RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Supply clock to GPIO
GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk); // clear PA4
GPIOA->MODER |= 1 << GPIO_MODER_MODE4_Pos; // Set PA4 to output (01)
GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk); // clear PA5
GPIOA->MODER |= 2 << GPIO_MODER_MODE5_Pos; // set PA5 to Alternate Function mode (10)
GPIOA->MODER &= ~(GPIO_MODER_MODE7_Msk); // clear PA7
GPIOA->MODER |= 2 << GPIO_MODER_MODE7_Pos; // set PA7 to alternate function mode (10)
GPIOA->MODER &= ~(GPIO_MODER_MODE1_Msk); //clear PA1
GPIOA->MODER |= 1 << GPIO_MODER_MODE1_Pos ; // set PA1 to output (01)
GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk); // Clear PA0
GPIOA->MODER |= 1<< GPIO_MODER_MODE0_Pos; // set PA0 to output (01)
}

void init_spi(void)
{
// rewrote spi initialization, seemed to be the root of alot of general issue with writting to the display
// Compared to some other groups spi initialization from the display lab
// alot of previous code utilized &=~ which appears unneeded
	
RCC->APB2ENR |= (1U << RCC_APB2ENR_SPI1EN_Pos);
SPI1->CR1 |= (1U << SPI_CR1_CPHA_Pos);
SPI1->CR1 |= (1U << SPI_CR1_CPOL_Pos);
SPI1->CR1 |= (1U << SPI_CR1_MSTR_Pos); // Set to Master Configuration
SPI1->CR1 |= (1U << SPI_CR1_SSI_Pos); // SSI
SPI1->CR1 |= (1U << SPI_CR1_SSM_Pos) ; // slave management 
SPI1->CR1 |= (3U << SPI_CR1_BR_Pos); // fPCLK/16
SPI1->CR1 |= (SPI_CR1_SPE); // Peripheral enabled
}

void reset(void) 
{ 
GPIOA->ODR |= (1U << 0);// 0 is the reset line    // old code used really long wasteful ammounts of time here
for( volatile int32_t n =0; n<8; n++){}// delay loop to give the line enough time high / low
GPIOA->ODR &= ~(1U << 0);
for( volatile int32_t n =0; n<16; n++){}
GPIOA->ODR |= (1U <<0);
for( volatile int32_t n =0; n<8; n++){}
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
send_packet(0x10); // still not sending FA and 90, shouldnt be needed
send_packet(0xAF);
}

void send_packet(uint32_t packet)
{
GPIOA->ODR &= ~(1U << 4); // CS0
SPI1->DR = packet;
for( volatile int16_t n =0; n<5; n++){}
while( SPI1->SR & SPI_SR_BSY) {} //loop until SPI completed.  Not sure if this is a busy wait will need to verify its allowed
GPIOA->ODR |= (1U << 4);
}

void CDLow (void) // easier than remembering which ouput is the CD line
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
		for (int16_t m=0; m<102; m++)// sets the length of the page to 0
			{send_packet(0x00);}
	}
}

void column_reset(void)
{
CDLow();
send_packet(0x00); // LSB to 0
send_packet(0x10); // MSB to 0
CDHigh();
}


void set_page(uint32_t page){ // should be an int 1-8 and will set the corrosponding page
CDLow();// CD low to write commands
int page0address = 176; // starting dec value for page 0
int newpage = page0address+(page-1); // page - 1 because page 1 is = page 0 but 1 makes more sense
send_packet(newpage);
column_reset();// resets the columns on page change
CDHigh();
}


void set_square(uint32_t x){ // takes a column fro 1-12 and draws a square in that spot
CDLow();
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
for(int16_t m=0; m<8; m++)
{
send_packet(0xFF); // doesnt have to be a solid sqaure but thats the easiest
}
column_reset();
}


void clear_square(uint32_t x){
CDLow(); // command mode
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

void DrawSquare(int BoardPosition){
	int column = (BoardPosition % 12); // sets the column as the remainder after a division by 12
	int page = (BoardPosition / 12.01)+1; // the 0.01 is for end values 12/12=1 but it is still page 1  // +1 because set page accepts values 1-8 not 0
	if (column==0){column=12;} // for instances with no remainder 96%12=0 which will always be column 12
	set_page(page);
	set_square(column);
}

void ClearSquare(int BoardPosition){
	int column = (BoardPosition % 12); // sets the column as the remainder after a division by 12
	int page = (BoardPosition / 12.01)+1; // the 0.01 is for end values 12/12=1 but it is still page 1  // +1 because set page accepts values 1-8 not 0
	if (column==0){column=12;} // for instances with no remainder 96%12=0 which will always be column 12
	set_page(page);
	clear_square(column);
}

void gameoveranimation(){ // simple animation to play on gameover
	for (volatile int32_t i = 1; i <= 12; i++){
for (volatile int32_t i = 0; i < 123456; i++){}
DrawSquare(i);
DrawSquare(i+12);
DrawSquare(i+24);
DrawSquare(i+36);
DrawSquare(i+48);
DrawSquare(i+60);
DrawSquare(i+72);
DrawSquare(i+84);
	
ClearSquare(i+12-1);
ClearSquare(i+24-1);
ClearSquare(i+36-1);
ClearSquare(i+48-1);
ClearSquare(i+60-1);
ClearSquare(i+72-1);
ClearSquare(i+84-1);
ClearSquare(i-1);
	
	if(i==12){
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

//int main(void)
void Display()
{
if (Isinitialized==false){ // will only run on first call
init_gpio(); // all the initialization stuff for the display will need moved to start of actual main / their own function
CDLow();
init_spi() ;
reset();
init_display();
CDHigh();
clear_all();
Isinitialized=true;
}
else{

randomcondition=true; // stuff only works in the while loop, this is a dummy holder

while(randomcondition==true){
// just testing positioning, seem to be all working
	
// will be reading 2 values from a queue, a draw square and a clear square	
// it will never have to draw more than 1 square in any given move

	// Standard move: Draw new head and clear old head
	// Gained fruit: Draw new fruit, no clear as snake gets bigger
	
	int16_t msg;
	int16_t msg2;
	read_q(&Locations, &msg);  // cant seem to figure this out
	read_q(&Locations, &msg2);
	
	
	
	if(msg==123 && msg2==123){gameoveranimation();} // will have logic for game over animation
	else{DrawSquare(msg);}
	for (volatile int32_t i = 0; i < 123456; i++){}
	if(msg2>96){
		msg2=msg2-96;
		DrawSquare(msg2);
	  }
	else{
		ClearSquare(msg2);
	}
	//for (volatile int32_t i = 0; i < 123456; i++){}
	
// simulated snake movement
	//DrawSquare(msg);
	//DrawSquare(msg2);
	
	/*
DrawSquare(39);
for (volatile int32_t i = 0; i < 123456; i++){}

DrawSquare(40);
ClearSquare(39);
for (volatile int32_t i = 0; i < 123456; i++){}
	
DrawSquare(41);
ClearSquare(40);
for (volatile int32_t i = 0; i < 123456; i++){}
	
DrawSquare(42);
ClearSquare(41);
for (volatile int32_t i = 0; i < 123456; i++){}
	
DrawSquare(30);
ClearSquare(42);
for (volatile int32_t i = 0; i < 123456; i++){}
	
DrawSquare(29);
ClearSquare(30);
for (volatile int32_t i = 0; i < 123456; i++){}
	
DrawSquare(28);
ClearSquare(29);
for (volatile int32_t i = 0; i < 123456; i++){}
	
DrawSquare(16);
ClearSquare(28);
for (volatile int32_t i = 0; i < 123456; i++){}
	
gameoveranimation(); // gamover also functions as a clear screen
	*/
	
randomcondition = false;

}
}


}