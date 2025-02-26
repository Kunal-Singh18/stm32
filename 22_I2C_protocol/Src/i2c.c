#include "stm32f4xx.h"
#include "i2c.h"

#define   GPIOBEN         (1U<<1)
#define   I2C1EN          (1U<<21)
#define   I2C1_SWRST      (1U<<15)


#define   I2C_100KHZ                 80 // 0B 0101 0000 =Decimal =80
#define   SD_MODE_MAX_RISE_TIME      17
#define   CR1_PE          (1U<<0)


void i2c_init(void)
{
	/*             configure GPIOx                     */


	// clock access to GPIOB
	RCC->AHB1ENR|=GPIOBEN;

	// enable SDA and SCL line in alternate function mapping of PB8 and PB9
	// PB8= SCL
	// PB9 =SDA
	// set booth pins to alternate function type
	GPIOB->MODER |=(1U<<17);
	GPIOB->MODER &=~(1U<<16);
	GPIOB->MODER |=(1U<<19);
	GPIOB->MODER &=~(1U<<18);

	//SET output drain in output type register
	GPIOB->OTYPER |=(1U<<8);
	GPIOB->OTYPER |=(1U<<9);

	//enable pull up resistor for PB8 and PB9
	GPIOB->PUPDR |=(1U<<16);
	GPIOB->PUPDR &=~(1U<<17);
	GPIOB->PUPDR |=(1U<<18);
	GPIOB->PUPDR &=~(1U<<19);

	//set alternate function type to AF04
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);


	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);


	/*      configure I2C      */
	// ENABLE CLOCK ACCESS
	RCC->APB1ENR |=I2C1EN ;

	//Reset mode
	I2C1->CR1 |= I2C1_SWRST;

	// come out of reset mode
	I2C1->CR1 &= ~I2C1_SWRST;

	//set peripheral clock frequency
	I2C1->CR2  |= (1U<<4);

	// set I2C TO STANDARD MODE ,100kHz clock
	I2C1->CCR = I2C_100KHZ;

	// set rise time
	I2C1->TRISE =SD_MODE_MAX_RISE_TIME;

	// ENABLE I2C
	I2C1->CR1 |=CR1_PE;

	/*It's important to note that the specific values used in the code, such as I2C_100KHZ and SD_MODE_MAX_RISE_TIME, are dependent on the desired configuration and the characteristics of your particular I2C communication setup.
	 * You may need to adjust these values based on your specific requirements and the hardware characteristics.
	 * */

}


#define  SR2_BUSY    (1U<<1)
#define  CR1_START   (1U<<8)
#define  SR1_SB      (1U<<0)
#define  SR1_ADDR    (1U<<1)
#define  SR1_TxE     (1U<<7)
#define  SR1_RxNE    (1U<<6)
#define  CR1_ACK     (1U<<10)
#define  CR1_STOP    (1U<<9)



void I2C1_ByteRead(char saddr,char maddr,char* data)// address of slave,memory address within slave that we want to read from and third argument is the pointer of the data that we want to store the read data to.
{
	// make a variable to empty status register

	volatile int temp=0;

	// wait until bus is not busy
	while(I2C1->SR2 & SR2_BUSY)
	{}

	// generate start condition
	I2C1->CR1 |=CR1_START;

	// wait for start
	while(!(I2C1->SR1 & SR1_SB))
	{}

	//transmit slave address + write mode
	I2C1->DR=saddr<<1;

	//wait for address flag
	while(!(I2C1->DR & SR1_ADDR))
	{}

	//clear flag by reading data from status register
	temp=I2C1->SR2;

	// send memory address that we want to read
	I2C1->DR= maddr;

	// wait until transmitter is empty
	while(!(I2C1->SR1 &SR1_TxE))
	{}

	// generate REstart condition
		I2C1->CR1|=CR1_START;

	// wait for REstart
		while(!(I2C1->SR1 & SR1_SB))
		{}

        // transmit slave address + read mode
	    I2C1->DR=saddr<<1 | 1;

	    //wait until address flag is set

		while(!(I2C1->DR &SR1_ADDR))
		{}

		//disable acknowlegdement bit
		I2C1->CR1 &=~CR1_ACK;


		//clear address flag by reading data from status register
		temp=I2C1->SR2;

		// generate stop condition
		I2C1->CR1 |=CR1_STOP;

		//Wait until RXNE flag is set
		while(!(I2C1->SR1 & SR1_RxNE))
		{}

		// READ from DATA REGISTER
		*data++ = I2C1->DR;



}
void  I2C1_BurstRead(char saddr,char maddr,int n,char* data)
{
	// make a variable to empty status register
		volatile int tmp=0;

		// wait until the bus is not empty

		while(I2C1->SR2 & SR2_BUSY)
			{}

			// generate start condition
			I2C1->CR1 |=CR1_START;

			// wait for start
			while(!(I2C1->SR1 & SR1_SB))
			{}

			// transmit slave address and write
			// for write put 0 at least significant bit
			I2C1->DR =saddr<<1;

			//wait for address flag
			while(!(I2C1->DR &SR1_ADDR))
			{}

			// clear status register by reading from it
			tmp=I2C1->SR2;

			// wait until transmitter is empty
			// means data register is now empty as transmission is complete

			while(!(I2C1->SR1 & SR1_TxE))
			{}

			// send memory address that we want to read
			I2C1->DR= maddr;

			// wait until transmitter is empty
	        while(!(I2C1->SR1 & SR1_TxE))
			{}
	        // generate a restart condition
	        I2C1->CR1 |=CR1_START;

	        // wait for start
	        while(!(I2C1->SR1 & SR1_SB))
	        {}

	        //transmit the slave address and read
	        I2C1->DR= saddr<<1 |1;

	        //wait for address flag
	        while(!(I2C1->DR &SR1_ADDR))
	        {}

	        // clear status register flag
	        tmp=I2C1->SR2;

	        // enable acknowledgment bit
	        I2C1->CR1 |=CR1_ACK;

	        while(n>0U)
	        {
	        	// we will check if one byte is left here and we will decrement the value  of n

	        	if(n==1U)// only one byte is left
	        	{
	        		// disable the acknowlegement bit
	        		I2C1->CR1 &=~CR1_ACK;

	        		// generate stop
	        		I2C1->CR1 |=CR1_STOP;

	        		// wait for RXnE flag to be set
	        		while(!(I2C1->SR1 & SR1_RxNE))
	        		{}

	        		// read from the data register
	        		*data++=I2C1->DR;

	        		break;

	        	}
	        	else
	        	{
	        		// wait for RXnE flag to be set
	        		while(!(I2C1->SR1 & SR1_RxNE))
	        		{}

	        		//read from the data register
	        		*data++=I2C1->DR;

	        		n--;
	        	}
	        }
}

#define SR1_BTF  (1U<<2)


void I2C1_burstWrite(char saddr,char maddr,int n ,char* data)// this time we will write to the slave device
{
	volatile int tmp=0;

	// wait until the bus is not busy
	while(I2C1->SR2 & SR2_BUSY)
	{}

	// generate start condition
	I2C1->CR1 |=CR1_START;

	// wait for start
	while(!(I2C1->SR1 & SR1_SB))
	{}

	// transmit slave address and write
	I2C1->DR =saddr<<1;

	//wait for address flag
	while(!(I2C1->DR &SR1_ADDR))
	{}

	// clear status register by reading from it
	tmp=I2C1->SR2;

	// wait until transmitter is empty
	// means data register is now empty as transmission is complete
	while(!(I2C1->SR1 & SR1_TxE))
	{}

	// send memory address
	I2C1->DR= maddr;

	for(int i=0;i<n;i++)
	{
		// wait until data register is empty
		while(!(I2C1->SR1 & SR1_TxE))
		{}

		// transmit memory address
		I2C1->DR = *data++;// it will point to the next address because the written element is something like array


	}
	// wait until transfer is finished
	while(!(I2C1->SR1 & SR1_BTF ))
	{
	}


}









