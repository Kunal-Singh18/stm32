 /*
  *here we achieve same task of toggling LEDS
  *here but instead of using the registers we achieve that by using the structures of the type base addresses .
 */

#include <stdint.h>

#define PERIPH_BASE                (0x40000000UL)

#define AHB1PERIPH_OFFSET          (0x00002000UL)
#define AHB1PERIPH_BASE            (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET               (0x0C00UL)
#define GPIOD_BASE                 (AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET                (0x3800UL)
#define RCC_BASE                  (AHB1PERIPH_BASE + RCC_OFFSET)


#define PIN12                        (1U<<12)// used for adjusting value of pin12 in output data register.
#define LED_PIN                      PIN12


#define GPIODEN                    (1U<<3)

#define __IO         volatile



typedef struct
{
	__IO uint32_t MODER;
	__IO uint32_t dummy[4];
	__IO uint32_t ODR;

}GPIO_TypeDef;

typedef struct
{
	__IO uint32_t dummy[12];
	__IO uint32_t AHB1ENR;

}RCC_TypeDef;


#define RCC            ((RCC_TypeDef*)RCC_BASE)  // "treat the address RCC_BASE as a pointer to an RCC_TypeDef structure."
#define GPIOD          ((GPIO_TypeDef*)GPIOD_BASE)


int main(void)
{
	/* 1. enable clock access to GPIOD */
	RCC->AHB1ENR |=GPIODEN;

	/* 2. set the pin12 as output pin */
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);





	while(1)
	{
		/*3. toggle the LED pin*/
		GPIOD->ODR ^=LED_PIN;

		for(int i=0;i<100000;i++)
		{
			// delay.
		}

	}
}




