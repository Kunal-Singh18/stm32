#include  "stm32f4xx.h"

#define   SYSTICK_LOAD       16000
#define   CTRL_ENABLE        (1U<<0)
#define   CTRL_CLKSRC        (1U<<2)
#define   CTRL_COUNTFLAG     (1U<<16)
#define   CONST_LOAD         16000000
#define   CTRL_TICKINT       (1U<<1)

void systickDelayMs(int delay)
{
	/*Configure systick */
	/*reload with number of clocks per millisecond*/
	SysTick->LOAD =SYSTICK_LOAD;

	/*clear systick current value register*/
	SysTick->VAL=0;
	/*enable systick and select internal clock source.*/
	SysTick->CTRL =CTRL_ENABLE | CTRL_CLKSRC;
	for(int i=0;i<delay;i++)
	{
		/*wait until the COUNTERFLAG is set*/
		while(!(SysTick->CTRL & CTRL_COUNTFLAG))
		{}
	}
	SysTick->CTRL=0;

}
void systick_interrupt(void)
{
	/*load value into load register*/
	SysTick->LOAD =CONST_LOAD - 1;// constant load for interrupting in 1 second

	/*clear Systick current value register*/
	SysTick->VAL=0;

	/*enable Systick and select internal clock source.*/
	SysTick->CTRL =CTRL_ENABLE | CTRL_CLKSRC;

	/*Enable Systick interrupt*/
	SysTick->CTRL |=CTRL_TICKINT;

}
