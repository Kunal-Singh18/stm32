 /*
  * for toggling an led we should locate the port and pin to which led is connected.
refer nucleo guide for the same.
 PD12
 */


#define PERIPH_BASE                (0x40000000UL)

#define AHB1PERIPH_OFFSET          (0x00002000UL)
#define AHB1PERIPH_BASE            (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET               (0x0C00UL)
#define GPIOD_BASE                 (AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET                (0x3800UL)
#define RCC_BASE                  (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET            (0x30UL)
#define RCC_AHB1EN_R                   (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET                 (0x00UL)
#define GPIOD_MODER_R                 (*(volatile unsigned int *)(GPIOD_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET                 (0x14UL)
#define GPIOD_OD_R                  (*(volatile unsigned int *)(GPIOD_BASE + OD_R_OFFSET))


#define PIN12                        (1U<<12)// used for adjusting value of pin12 in output data register.
#define LED_PIN                      PIN12


#define GPIODEN                    (1U<<3)


int main(void)
{
	/* 1. enable clock access to GPIOD */
	RCC_AHB1EN_R |=GPIODEN;

	/* 2. set the pin12 as output pin */
	GPIOD_MODER_R |= (1U<<24);
	GPIOD_MODER_R &= ~(1U<<25);





	while(1)
	{
		/*3. toggle the LED pin*/
		GPIOD_OD_R |=LED_PIN;

	}
}




