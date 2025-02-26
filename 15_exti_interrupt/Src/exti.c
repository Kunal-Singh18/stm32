#include "exti.h"

#define  GPIOAEN     (1U<<0)
#define  SYSCFGEN    (1U<<14)


void pa0_exti_init(void)
{
	/*Disable global interrupt */
	__disable_irq();
	/* Enable clock access for GPIOA */
	RCC->AHB1ENR |=GPIOAEN;

	/* set PA0 as input pin*/
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<0);

	/* enable clock access to SYSCFG*/
	RCC->APB2ENR |=SYSCFGEN;

	/* select PORTA for EXTI0*/
	SYSCFG->EXTICR[0] = 0;

	/*Unmask EXTI0 */
	EXTI->IMR |=(1U<<0);

	/* select falling edge trigger*/
	EXTI->FTSR |=(1U<<0);
	/*enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI0_IRQn);
	/* enable global interrupt*/
	__enable_irq();

}
