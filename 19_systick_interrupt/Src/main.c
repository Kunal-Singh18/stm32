/*
 * This project is a sub project under UART communication driver development
 * Here we implement  a retargeting printf  exercise where we retarget the output of printf from console to our UART
 * */


#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>
#include  "uart.h"
#include  "adc.h"
#include  "systick.h"



#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12


#define GPIODEN                    (1U<<3)

static void systick_callback(void);

int main(void)
{

	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	 uart2_tx_init();
	 systick_interrupt();

	while(1)
	{



	}

}
static void systick_callback(void)
{
	printf("one second passed \n\r");
	GPIOD->ODR  ^=LED_PIN;

}
void SysTick_Handler(void)
{
	systick_callback();
}

