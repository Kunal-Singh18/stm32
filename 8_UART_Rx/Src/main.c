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

char key;

int main(void)
{
	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);


	uart2_txrx_init();

	while(1)
	{
		key=uart2_read();
		if(key=='1')
		{
			GPIOD->ODR |=LED_PIN ;
		}
		else
		{
			GPIOD->ODR &=~LED_PIN;
		}
	}

}

