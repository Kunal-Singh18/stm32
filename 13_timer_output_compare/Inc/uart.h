
#ifndef UART_H_
#define UART_H_

#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>

void uart2_tx_init(void);
char uart2_read(void);
void uart2_txrx_init(void);

#endif /* UART_H_ */
