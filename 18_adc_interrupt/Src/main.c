/*
 * This project is a sub project under UART communication driver development
 * Here we implement  a retargeting printf  exercise where we retarget the output of printf from console to our UART
 * */


#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>
#include  "uart.h"
#include "adc.h"


uint32_t value;

int main(void)
{
	uart2_txrx_init();
	pf3_adc_interrupt_init();
	start_conversion();

	while(1)
	{

	}

}
static void adc_callback(void)
{
	value=adc_read();// make sure that in read function we remove loop as we rely on interrupt mechanism to check the EOC flag
	printf("%d \n\r",value);
}

void ADC_IRQHandler(void)
{
	/*check for EOC flag*/
	if(ADC3->SR & SR_EOC)
	{
		//callback
		adc_callback();

		//clear EOC bit
		ADC3->SR &= ~SR_EOC;
	}
}
