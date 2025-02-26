/*
 * This project is a sub project under UART communication driver development
 * Here we implement  a retargeting printf  exercise where we retarget the output of printf from console to our UART
 * */


#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>

#include  "uart.h"

#define GPIODEN    (1U<<3)
#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12



static void DMA_callback(void);
int main(void)
{

	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	char src_buffer[23]="This is a DMA operation";

	uart2_tx_init();
	dma_1_stream6_init((uint32_t) src_buffer,(uint32_t) &USART2->DR,23);

	while(1)
	{


	}

}
static void DMA_callback(void)
{
	GPIOD->ODR ^=LED_PIN;
	for(int i=0;i<1000000;i++)
	{
		//delay
	}
}

void DMA1_Stream6_IRQHandler(void)
{
	/* Check for transfer complete interrupt */
    if(DMA1->HISR & HSIR_TCIF6)
    {
    	/*Clear Flag*/
    	DMA1->HIFCR |=HIFCR_CTCIF6;

    	/*Do something*/
    	DMA_callback();
    }

}
