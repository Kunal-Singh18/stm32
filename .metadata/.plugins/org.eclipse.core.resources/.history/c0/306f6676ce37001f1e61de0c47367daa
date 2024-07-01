
/*this firmware aims to achieve the toggling of led connected to PD12 in a modular way by using the header file containing all the addresses which we
 define earlier all by ourselves with help of documentations and memory mapping.
 * */


#include  "stm32f4xx.h"

#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12


#define GPIODEN                    (1U<<3)


int main(void)
{
	RCC->AHB1ENR |=GPIODEN;


	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);


	while(1)
	{
		GPIOD->ODR ^=LED_PIN;

		for(int i=0;i<1000000;i++)
		{

		}
	}

}
