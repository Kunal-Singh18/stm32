

#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>
#include  "uart.h"
#include  "adc.h"
#include  "systick.h"
#include  "timer.h"



#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12


#define GPIODEN                    (1U<<3)


static void tim3_callback(void);
int main(void)
{

	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	 uart2_tx_init();
	 tim3_1hz_interrupt_init();

	while(1)
	{
	}

}

static void tim3_callback(void)
{
	printf("one second passed tt \n\r");
	GPIOD->ODR  ^=LED_PIN;
}

void TIM3_IRQHandler(void)
{
	/*Clear update interrupt flag*/
	TIM3->SR &=~SR_UIF;

	//perform something
	tim3_callback();
}

