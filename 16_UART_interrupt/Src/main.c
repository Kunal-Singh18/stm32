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

static void uart_callback(void);

int key;
int main(void)
{
	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);


	uart2_tx_interrupt_init();

	while(1)
	{
		// we kept this empty as TXE is empty by default so we make the execution interrupt oriented
	}

}
static void uart_callback(void)
{
	//do something.
	printf("hello world from lesner \n\r");
	GPIOD->ODR ^=(LED_PIN);
	for (volatile int i = 0; i < 1000000; ++i); // Simple delay
}
void USART2_IRQHandler(void)
{
	/*check if TXE is set*/
	if(USART2->SR & SR_TXE)
	{
		uart_callback();

		//clear the TXE flag
		USART2->SR &=~(SR_TXE);

	}
}
