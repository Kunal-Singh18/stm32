/*
 * adxl.h
 *
 *  Created on: Jul 28, 2024
 *      Author: kunal
 */
#include "stdint.h"

#ifndef ADXL_H_
#define ADXL_H_

#include "i2c.h"


#define   DEVID_R       0x00
//put R to indicate this is register from the data sheet  type
// these all are 8 bit registers
#define   DEVICE_ADDR        0x53
#define   DATA_FORMAT_R      0x31
#define   POWER_CTL_R        0x2D
#define   DATA_START_ADDR    0x32


// THESE BELOW BITS CAN BE FOUND READING THE DATSHEET

#define  FOUR_G                0x01 // CONFIGURE DATA FORMAT REG VALUE RANGE
#define  RESET                 0x00 // RESET
#define  SET_MEASURE_B         0x08 // SET MEASURE AND WAKEUP AT 8 HERTZ.This is the standard value used




//exposing functions over here
void adxl_init(void);

void adxl_read_address(uint8_t reg);
void adxl_read_value(uint8_t reg);
void adxl_write(uint8_t reg,char value);

#endif /* ADXL_H_ */
