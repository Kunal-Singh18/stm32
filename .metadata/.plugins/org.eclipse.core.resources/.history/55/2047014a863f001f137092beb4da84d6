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
	pf3_adc_init();
	start_conversion();

	while(1)
	{
		value=adc_read();
		printf("%d \n\r",value);
	}

}

