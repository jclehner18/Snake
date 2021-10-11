#include "stm32l053xx.h"
void init_spi(void);
void send_packet(uint32_t packet);
void init_gpio(void);
void init_sequence(uint32_t data);
void Reset(void);
void set_display(uint32_t set);
void reset_all_columns(void);

void init_gpio(void)
{
	RCC->IOPENR|=RCC_IOPENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk);
	GPIOA->MODER |= 1<<GPIO_MODER_MODE4_Pos;              
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= 2<<GPIO_MODER_MODE5_Pos;              
	GPIOA->MODER &= ~(GPIO_MODER_MODE7_Msk);
	GPIOA->MODER |= 2<<GPIO_MODER_MODE7_Pos;            
	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk);
	GPIOA->MODER |= 1<<GPIO_MODER_MODE0_Pos;              
	GPIOA->MODER &= ~(GPIO_MODER_MODE1_Msk);  //pin 26 CD
	GPIOA->MODER |= 1<<GPIO_MODER_MODE1_Pos;      


	RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	GPIOC->MODER &= ~(GPIO_MODER_MODE13_Msk);  //PC13 aka button

}

void init_spi(void)
{            
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	SPI1->CR1 &= ~(SPI_CR1_CPHA); //clock phase 0
	SPI1->CR1 |= (SPI_CR1_CPOL); //polarity 1
	SPI1->CR1 |= (SPI_CR1_MSTR); //master
	SPI1->CR1 &= ~(SPI_CR1_BR_0); //baudrate        100        
	SPI1->CR1 &= ~(SPI_CR1_BR_1);
	SPI1->CR1 |= (SPI_CR1_BR_2);
	SPI1->CR1 &= ~(SPI_CR1_LSBFIRST); //LSB
	SPI1->CR1 |= (SPI_CR1_SSI); //SSI
	SPI1->CR1 |= (SPI_CR1_SSM); //SSM
	SPI1->CR1 &= ~(SPI_CR1_RXONLY); //transmit and receive
	SPI1->CR1 &= ~(SPI_CR1_DFF); //DFF
	//SPI1->CR1 &= ~(SPI_CR1_CRCNEXT); //crnext
	//SPI1->CR1 &= ~(SPI_CR1_CRCEN);
	//SPI1->CR1 &= ~(SPI_CR1_BIDIOE);
	//SPI1->CR1 &= ~(SPI_CR1_BIDIMODE);
	SPI1->CR1 |= (SPI_CR1_SPE); //enable
}

void send_packet(uint32_t packet)
{
	GPIOA->ODR |= (1U<<1);
	SPI1->DR = packet;               //can send anything we want to
	for (volatile int32_t i = 0; i < 3; i++){} //delay loop for select to start after the clock
	while(SPI1->SR & SPI_SR_BSY) {} //wait until SPI xmit is complete
	GPIOA->ODR &= ~(1U<<1);
	GPIOA->ODR &= ~(1U<<4);
}

void init_sequence(uint32_t data)
{            
	GPIOA->ODR &= ~(1U<<4);
	SPI1->DR = data;            
	for (volatile int32_t i = 0; i < 7; i++){}
	while(SPI1->SR & SPI_SR_BSY){}
	GPIOA->ODR |= (1U<<4);
	for (volatile int32_t i = 0; i < 7; i++){}
	GPIOA->ODR &= ~(1U<<4);// sets select low
}

void Reset(void)
{
	GPIOA->BSRR |= (1u<<0); // makes PA0 high
	for (volatile int32_t i = 0; i < 2000; i++){}
	GPIOA->BSRR = 0x00; //0x00  makes PA0 low
	GPIOA->ODR = 0x00;
	for (volatile int32_t i = 0; i < 2000; i++){}
	GPIOA->BSRR |= (1u<<0);  //makes PA0 high
	for (volatile int32_t i = 0; i < 2000; i++){}
}
void set_display(uint32_t set)
{
	GPIOA->ODR &= ~(1U<<1);
	GPIOA->ODR &= ~(1U<<4);
	SPI1->DR = set;               //can send anything we want to
	for (volatile int32_t i = 0; i < 3; i++){} //delay loop for select to start after the clock
	while(SPI1->SR & SPI_SR_BSY) {} //wait until SPI xmit is complete
	GPIOA->ODR |= (1U<<1);
	GPIOA->ODR |= (1U<<4);
}

void reset_all_columns(void)
{
	//176 to 183
	uint32_t x=176;
	while(x<=183){
	set_display(0x10);
	set_display(0x00);
	set_display(0x10);
	set_display(x);
	for(volatile uint32_t i=0; i<103; i++)
		{
			send_packet(0);
		}
			x++;
	}
}

int main(void)
{
	init_gpio();
	init_spi();
	for (volatile int32_t i = 0; i < 12; i++){}
	Reset();
	for (volatile int32_t i = 0; i < 12; i++){} //delay for the boot up sequence before first command
	init_sequence(0x40);
	init_sequence(0xA1);
	init_sequence(0xC0);
	init_sequence(0xA4);
	init_sequence(0xA6);
	init_sequence(0xA2);
	init_sequence(0x2F);
	init_sequence(0x27);
	init_sequence(0x81);
	init_sequence(0x10);
	init_sequence(0xAF);
	for (volatile int32_t i = 0; i < 12; i++){}
	reset_all_columns();
	
	while(1)
	{
		set_display(0x00);
	set_display(0x10);
	set_display(0xB0);
	for(volatile uint32_t i=0; i<8; i++)
	{
		send_packet(0xFF);
	}
	
	for (volatile int32_t i = 0; i < 123456; i++){}
	reset_all_columns();
	set_display(0x00);
	set_display(0x16);
	set_display(0xB0);
	for(volatile uint32_t i=0; i<8; i++)
	{
		send_packet(0xFF);
	}
	
	for (volatile int32_t i = 0; i < 123456; i++){}
	reset_all_columns();
	set_display(0x00);
	set_display(0x10);
	set_display(0xB7);
	for(volatile uint32_t i=0; i<8; i++)
	{
		send_packet(0xFF);
	}
	
	for (volatile int32_t i = 0; i < 123456; i++){}
	reset_all_columns();
	set_display(0x00);
	set_display(0x16);
	set_display(0xB7);
	for(volatile uint32_t i=0; i<8; i++)
	{
		send_packet(0xFF);
	}
	for (volatile int32_t i = 0; i < 123456; i++){}
	reset_all_columns();
	}
}
