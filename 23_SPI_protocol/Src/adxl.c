#include "adxl.h"
#include "stdint.h"


#define   MULTI_BYTE_EN      (0x40)
#define   READ_OPERATION     (0x80)


void adxl_read_address(uint8_t address,uint8_t *rx)
{

	/*Set read operation*/
	address |=READ_OPERATION;

	/*Enable multi-byte*/
	address |=MULTI_BYTE_EN;

	/*Pull cd line low to enable the slave*/
	cs_enable();

	/*send address */
	spi1_transmit(address,1);

	/*enable 6 bytes*/
	spi1_receive(rx,6);

}

void adxl_write(uint8_t address,uint8_t value)
{
uint8_t data[2];
/*Enable multi-byte,place address into bufffer*/
data[0]=address|MULTI_BYTE_EN;

/*place data into buffer*/
data[1]=value;


/*pull cs line low to enable slave*/
cs_enable();

/*Transmit data and address*/
spi1_transmit(data,2);

/*Pull cs line high to disable the slave.*/
cs_disable();


}


void adxl_init(void)
{

	/*enable the SPIO GPIO*/
	spi_gpio_init();

	/*Enable SPI config*/
	spi1_config();


	// set the data front range to +-4g
	adxl_write(DATA_FORMAT_R,FOUR_G);


	// reset all bits
	adxl_write(POWER_CTL_R,RESET );


	// configure power control measure bit
	adxl_write(POWER_CTL_R,SET_MEASURE_B);

}

