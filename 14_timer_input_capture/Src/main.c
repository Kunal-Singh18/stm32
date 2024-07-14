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


/*
 * while perfoming this exercise we should connect jumper from PD12 TO PA8
 * refer nucleo guide for the pins
 * and use timestamp as live expression*/

int timestamp=0;
int main(void)
{

	tim4_pd12_output_compare();
	tim1_pa8_input_capture();


	while(1)
	{
		//wait until edge is captured
		while(!(TIM1->SR &SR_CC1IF))
		{

		}
		//read the captured value,
		timestamp=TIM1->CCR1;
	}

}

