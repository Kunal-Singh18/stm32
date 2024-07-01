
/*this firmware aims to achieve the toggling of led connected to PD12 in a modular way by using the header file containing all the addresses which we
 define earlier all by ourselves with help of documentations and memory mapping.
 * */


#include  "stm32f4xx.h"

#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12

#define PIN0                        (1U<<0)
#define PUSH_BUTTON                 PIN0

#define GPIODEN                    (1U<<3)
#define GPIOAEN                     (1U<<0)



int main(void)
{
	/*enabling clock access to GPIOA and GPIOD */
	RCC->AHB1ENR |=GPIODEN;
	RCC->AHB1ENR |=GPIOAEN;

	/*setting pin modes*/
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);




	while(1)
	{
		if(GPIOA->IDR & PUSH_BUTTON)
		{
			//TURN ON LED
			GPIOD->BSRR =LED_PIN;
		}
		else
		{	//turn off led.
			GPIOD->BSRR = (1U<<28);
		}

	}

}
