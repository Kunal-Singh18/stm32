
#ifndef UART_H_
#define UART_H_

#include  "stm32f4xx.h"
#include  <stdint.h>
#include  <stdio.h>
#define SR_RXNE    (1U<<5)
#define HSIR_TCIF6   (1U<<21)
#define HIFCR_CTCIF6 (1U<<21)

void uart2_tx_init(void);
char uart2_read(void);
void uart2_txrx_init(void);
void uart2_rx_interrupt_init(void);
void dma_1_stream6_init(uint32_t src,uint32_t dst,uint32_t len);

#endif /* UART_H_ */
