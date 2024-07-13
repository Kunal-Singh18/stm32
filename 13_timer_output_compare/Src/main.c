/*
 * This project is a sub project under UART communication driver development
 * Here we implement  a retargeting printf  exercise where we retarget the output of printf from console to our UART
 * */


#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>
#include  "uart.h"
#include  "adc.h"
#include  "systick.h"
#include  "timer.h"





int main(void)
{/*our led pin PD12 is connected to TIM4 CH1 so we need to change accordngly for this exercise.
we will make changes in timer.c*/

	tim4_pd12_output_compare();


	while(1)
	{

	}

}

