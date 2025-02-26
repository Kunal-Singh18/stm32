#include "adxl.h"
#include "stdint.h"


char data;

uint8_t data_rec[6];

void adxl_read_address(uint8_t reg)
{
	I2C1_ByteRead(DEVICE_ADDR,reg,&data);
}

void adxl_write(uint8_t reg,char value)
{
	char data[1];

	data[0]=value;// buffer that contains the information that we want to write to the slave

	I2C1_burstWrite(DEVICE_ADDR,reg,1,data);

}

// since we have 6 data registers we will set the burst read length to 6

void adxl_read_value(uint8_t reg)
{
	 I2C1_BurstRead(DEVICE_ADDR,reg,6, (char*) data_rec);
}

void adxl_init(void)
{

	// enable the I2C module
	i2c_init();


	// read the DEVID,This should return 0xE5 // this is for verification purpose
	adxl_read_address(DEVID_R);


	// set the data front range to +-4g
	adxl_write(DATA_FORMAT_R,FOUR_G);


	// reset all bits
	adxl_write(POWER_CTL_R,RESET );


	// configure power control measure bit
	adxl_write(POWER_CTL_R,SET_MEASURE_B);

}

