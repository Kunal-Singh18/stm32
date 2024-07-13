#include "stm32f4xx.h"

#define TIM3EN    (1U<<1)
#define CR1_CEN        (1U<<0)


void tim3_1hz_init(void)
{
	//enable clock access
	RCC->APB1ENR = TIM3EN;

	// set prescaler value
	TIM3->PSC = 1600 -1;  //   16000000 / 1600 = 10000
	// set auto reload value
	TIM3->ARR = 10000 -1; // 10000/10000 = 1;
	// clear counter
	TIM3->CNT =0;
	// enable timer
	TIM3->CR1 =CR1_CEN;

}

