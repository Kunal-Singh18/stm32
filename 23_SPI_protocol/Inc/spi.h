/*
 * spi.h
 *
 *  Created on: Jul 30, 2024
 *      Author: kunal
 */

#ifndef SPI_H_
#define SPI_H_
#include "stdint.h"

void spi_gpio_init(void);
void spi1_config(void);
void spi1_transmit(uint8_t *data,uint32_t size);
void spi1_receive(uint8_t *data,uint32_t size);
void cs_enable(void);
void cs_disable(void);
#endif /* SPI_H_ */
