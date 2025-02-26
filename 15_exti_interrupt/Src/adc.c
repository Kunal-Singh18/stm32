#include "adc.h"

#define GPIOFEN         (1U<<5)
#define ADC3EN          (1U<<10)
#define ADC_CH9         9
#define ADC_SEQ_LEN     0x00
#define CR2_ADON       (1U<<0)
#define CR2_SWSTART     (1U<<30)
#define SR_EOC           (1U<<1)
#define CR2_CONT         (1U<<1)

void pf3_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);

void pf3_adc_init(void)
{
	/*Configure the GPIO module*/

	/*enable clock access to GPIOF*/
	RCC->AHB1ENR |=GPIOFEN;
	/*set the mode of pf3 to analog mode*/
	GPIOF->MODER &=~(1U<<6);
	GPIOF->MODER &=~(1U<<7);


	/*Configure the ADC module*/

	/*enable clock access to ADC3*/
	RCC->APB2ENR |=ADC3EN;

	/*configure the adc parameters*/

	/**conversion sequence start/	 */
	ADC3->SQR3 =ADC_CH9 ;
	/*conversion sequence length*/
	ADC3->SQR1 =0x00;// since sequence length is 1 therefore we can directly set it to zero.

	/*enable ADC module*/
	ADC3->CR2 |=CR2_ADON;
}

void start_conversion(void)
{
	/*Enable continuos conversion*/
	ADC3->CR2 |=CR2_CONT;

	/* start the adc conversion */
	ADC3->CR2 |=CR2_SWSTART;// SW indicates software trigger as trigger can be some sort of timer also.
	// our conversion may start after some timer also.

}

uint32_t adc_read(void)
{
	/*wait for the conversion to be complete*/
	while(!(ADC3->SR & SR_EOC))
	{
		// wait
	}

	/*read the converted data*/
	return ADC3->DR;
}




