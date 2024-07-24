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
#include  "timer.h"
#include  "exti.h"


#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12


#define GPIODEN                    (1U<<3)


static void exti_callback(void);

int main(void)
{

	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	uart2_tx_init();
	pa0_exti_init();

	while(1)
	{

	}

}
static void exti_callback(void)
{
	printf("button is pressed");
	GPIOD->ODR ^=LED_PIN;
}
void EXTI0_IRQHandler(void)// exactly same name as defined in vector table.
{
	//checking line of interrupt
	if(EXTI->PR & LINE0)// useful in case when multiple lines have same IRQ
	{
		/*clear PR flag*/
		EXTI->PR |=LINE0;
		//perform something.
		exti_callback();
	}
}
