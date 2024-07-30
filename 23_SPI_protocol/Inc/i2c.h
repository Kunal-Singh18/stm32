/*
 * i2c.h
 *
 *  Created on: Jul 27, 2024
 *      Author: kunal
 */

#ifndef I2C_H_
#define I2C_H_
void i2c_init(void);
void I2C1_ByteRead(char saddr,char maddr,char* data);
void  I2C1_BurstRead(char saddr,char maddr,int n,char* data);
void I2C1_burstWrite(char saddr,char maddr,int n ,char* data);


#endif /* I2C_H_ */
