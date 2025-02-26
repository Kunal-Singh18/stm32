#include "stm32f4xx.h"

#define TIM4EN    (1U<<2)
#define TIM3EN    (1U<<1)
#define TIM1EN    (1U<<0)
#define CR1_CEN        (1U<<0)
#define CCER_CC1E      (1U<<0)

#define GPIODEN     (1U<<3)
#define GPIOAEN     (1U<<0)
#define CCMR1_CC1S  (1U<<0)

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
void tim4_pd12_output_compare(void)
{
	/*enable clock access to GPIOD*/
	RCC->AHB1ENR |=GPIODEN;

	/*set pin mode as ALTERNATE type*/
	GPIOD->MODER &= ~(1U<<24);
	GPIOD->MODER |= (1U<<25);

	/*set alternate function type as TIM4 CH1 AF02*/
	GPIOD->AFR[1] &=~(1U<<16);
	GPIOD->AFR[1] |=(1U<<17);
	GPIOD->AFR[1] &=~(1U<<18);
	GPIOD->AFR[1] &=~(1U<<19);

	//enable clock access
	RCC->APB1ENR = TIM4EN;

	// set prescaler value
	TIM4->PSC = 1600 -1;  //   16000000 / 1600 = 10000
	// set auto reload value
	TIM4->ARR = 10000 -1; // 10000/10000 = 1;

	/*set output compare toggle mode*/
	TIM4->CCMR1 |=(1U<<4);
	TIM4->CCMR1 |=(1U<<5);

	/*enable tim4 ch1 in compare mode*/
	TIM4->CCER |=CCER_CC1E;


	// clear counter
	TIM4->CNT =0;
	// enable timer
	TIM4->CR1 =CR1_CEN;

}

void tim1_pa8_input_capture(void)
{
	/*enable clock access to GPIOD*/
	RCC->AHB1ENR |=GPIOAEN;

	/*set pin mode of PA8 as ALTERNATE type*/
	GPIOA->MODER &= ~(1U<<16);
	GPIOA->MODER |= (1U<<17);

	/*set alternate function type as TIM1_CH1 AF01*/
	GPIOA->AFR[1] |=(1U<<0);
	GPIOA->AFR[1] &=~(1U<<1);
	GPIOA->AFR[1] &=~(1U<<2);
	GPIOA->AFR[1] &=~(1U<<3);

	/*enable clock access to Timer1*/
	RCC->APB2ENR |=TIM1EN;

	/*set prescaler value*/
	TIM1->PSC=1600-1;

	/*Set CH1 to capture at every edge*/
	TIM1->CCMR1 |=(1U<<0);// this over here sets in input mode deafult is output mode.
	TIM1->CCMR1 &=~(1U<<1);

	/*Set CH1 to capture at rising edge */
	TIM1->CCER |=CCER_CC1E;

	/*enable TIM1*/
	TIM1->CR1 |=CR1_CEN;

}
