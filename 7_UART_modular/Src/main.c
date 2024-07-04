/*
 * This project is a sub project under UART communication driver development
 * Here we implement  a retargeting printf  exercise where we retarget the output of printf from console to our UART
 * */


#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>

#include  "uart.h"

int main(void)
{

	uart2_tx_init();

	while(1)
	{
		printf("hello world \n\r");

	}

}

