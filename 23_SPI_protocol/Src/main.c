/*
 * This project is a sub project under UART communication driver development
 * Here we implement  a retargeting printf  exercise where we retarget the output of printf from console to our UART
 * */


#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>

#include  "uart.h"

#define GPIODEN    (1U<<3)
#define PIN12                        (1U<<12)
#define LED_PIN                      PIN12

#include "adxl.h"

int16_t x,y,z;
float xg,yg,zg;

const float FOUR_G_SCLAE_FACT = 0.0078;

 uint8_t data_rec[6];

int main()
{
	adxl_init();

	while(1)
	{
		adxl_read_address(DATA_START_ADDR,data_rec);
		// we stored read values in a buffer named data_rec

		x=((data_rec[1]<<8)|data_rec[0]);
		y=((data_rec[3]<<8)|data_rec[2]);
		z=((data_rec[5]<<8)|data_rec[4]);


		xg = x * FOUR_G_SCLAE_FACT;
		yg = y * FOUR_G_SCLAE_FACT;
		zg = z * FOUR_G_SCLAE_FACT;

	}


}







