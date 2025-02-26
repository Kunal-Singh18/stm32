#include "spi.h"
#include "stdint.h"
#include "stm32f4xx.h"

#define SPI1EN     (1U<<12)
#define CR1_BR     (1U<<3)
#define CR1_CPHA   (1U<<0)
#define CR1_CPOL   (1U<<1)
#define CR1_RXONLY (1U<<12)
#define CR1_MSBFIRST (1U<<7)
#define CR1_MSTR    (1U<<2)
#define CR1_DFF    (1U<<11)
#define CR1_SSM    (1U<<9)
#define CR1_SSI    (1U<<8)
#define GPIOAEN    (1U<<0)
#define SR_TXE     (1U<<1)
#define SR_BSY     (1U<<7)
#define SR_RxNE    (1U<<0)

/*PINOUT
 *
 * PA5 - CLK
 * PA6 - MISO
 * PA7 - MOSI
 * PA9 - SS(we can use any line for slave select) and it has to be set to output mode.
 * */

void spi_gpio_init(void)
{

	/* enable clock access to GPIOA*/
	RCC->AHB1ENR |=GPIOAEN ;


	/*SET PA5,PA6,PA7 to alternate function type*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |=(1U<<11);

	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |=(1U<<13);


	GPIOA->MODER &=~(1U<<14);
	GPIOA->MODER |=(1U<<15);

	/*set PA9 to output type*/
	GPIOA->MODER &=~(1U<<19);
	GPIOA->MODER |=(1U<<18);

	/*set alternate function type of PA5,PA6,PA7 to AF05*/
	GPIOA->AFR[0]|=(1U<<20);
	GPIOA->AFR[0]&=~(1U<<21);
	GPIOA->AFR[0]|=(1U<<22);
	GPIOA->AFR[0]&=~(1U<<23);

	GPIOA->AFR[0]|=(1U<<24);
	GPIOA->AFR[0]&=~(1U<<25);
	GPIOA->AFR[0]|=(1U<<26);
	GPIOA->AFR[0]&=~(1U<<27);

	GPIOA->AFR[0]|=(1U<<28);
	GPIOA->AFR[0]&=~(1U<<29);
	GPIOA->AFR[0]|=(1U<<30);
	GPIOA->AFR[0]&=~(1U<<31);


}

void spi1_config(void)
{
	/*enable clock access to spi1*/
	RCC->AHB2ENR |=SPI1EN;

	/*clock speed to periphclk/4 in baud rate register*/
	SPI1->CR1 |=CR1_BR;
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 &=~(1U<<5);

	/*set CPOL and CPHA to 1*/
	SPI1->CR1 |=CR1_CPHA;
	SPI1->CR1 |=CR1_CPOL;

	/*enable full Duplex*/
	SPI1->CR1 &=~(CR1_RXONLY);

	/*enable MSB first*/
	SPI1->CR1 &=~CR1_MSBFIRST;

	/*set master mode*/
	SPI1->CR1 |=CR1_MSTR;

	/*set data size 8 BIT*/
	SPI1->CR1 &=~CR1_DFF;

	/*SET SS1 AND SSM TO 1;NSS is disabled by default*/
	SPI1->CR1|= CR1_SSM;
	SPI1->CR1|= CR1_SSI;

}

void spi1_transmit(uint8_t *data,uint32_t size)
{
	uint32_t i=0;// only used for loop purpose
	uint8_t temp=0;// This is for clearing flags by reading value

	while(i<size)
	{
		/*wait until TxE is set*/
		while(!(SR_TXE & SPI1->SR))
		{}

		/*write the data to the data register*/
		SPI1->DR=data[i];
		i++;
	}
	/*wait until TxE flag is set*/
	while(!(SR_TXE & SPI1->SR))
	{}

	/*wait for the busy flag to reset*/
	while(SPI1->SR &SR_BSY)
	{
	}

	/*clear over run flag by reading data from both status and data register*/
	temp=SPI1->DR;
	temp=SPI1->SR;

}

 void spi1_receive(uint8_t *data,uint32_t size)
 {
	 while(size)
	 {
		 /*send dummy data*/
		 SPI1->DR=0;

		 /*wait for RxNE flag to be set*/ // receiver not empty
		 while(!(SPI1->SR & SR_RxNE))
		 {

		 }

		 /*read data from data register*/
		 *data++=SPI1->DR;


		 --size;
	 }
 }

 void cs_enable(void)
 {
	 //set pin 9 to 0 inorder to enable it
	 //or we say pull cs line low in order to enable it
	 GPIOA->ODR &=~(1U<<9);

 }

void cs_disable(void)
{
	// pull pin9 high to disbale it
	GPIOA->ODR |=(1U<<9);
}

