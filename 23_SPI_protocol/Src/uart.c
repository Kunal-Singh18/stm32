#include "uart.h"


#define GPIOAEN                     (1U<<0)
#define USART2EN                    (1U<<17)

#define SYS_FREQ        16000000
#define UART_BaudRate   115200
#define APB1_CLK        SYS_FREQ // considering clock tree is not configured. then division factor is 1.

#define CR1_TE      (1U<<3)
#define CR1_UE      (1U<<13)
#define SR_TXE      (1U<<7)
#define CR1_RE      (1U<<2)
#define SR_RXNE     (1U<<5)
#define CR1_RXNEIE  (1U<<5)
#define DMA1EN      (1U<<21)
#define DMA_S_EN    (1U<<0)
#define CHSEL4        (1U<<27)
#define DMA_MINC      (1U<<10)
#define DMA_DIR_MEM_TO_PERIPH   (1U<<6)
#define DMA_TCIE      (1U<<4)
#define UART_CR1_DMAT  (1U<<7)
#define DMA_CIRC       (1U<<8)



char uart2_read(void);
static void uart_set_baudrate(USART_TypeDef * USARTx,uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate);
void uart2_write(int ch);


int __io_putchar(int ch)// modifying the runtime function of printf
{
	uart2_write(ch);
	return ch;
}
void uart2_txrx_init(void)// it enables both tx and rx
{
	/*CONFIGURE UART GPIO PIN*/

	/*enable clock access to GPIOA*/
	RCC->AHB1ENR |=GPIOAEN;

	/*set PA2 mode to alternate function type*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*set PA2 alternate function type to AF07(UART_TX)*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*set PA3 to alternate function type*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*set PA3 alternate function type to AF07*/
	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);


	/*CONFIGURE THE UART module*/
	/*enable clock access to uart2*/
	RCC->APB1ENR |=USART2EN;

	/*configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BaudRate);


	/*configure transfer direction*/
	USART2->CR1 =(CR1_TE |CR1_RE); // direct putting equal to so that other values are set to their default indicating default mode of action.

	/*enable uart module*/
	USART2->CR1 |=CR1_UE;


}

void uart2_rx_interrupt_init(void)// rx and its interrupt
{
	/*CONFIGURE UART GPIO PIN*/

	/*enable clock access to GPIOA*/
	RCC->AHB1ENR |=GPIOAEN;

	/*set PA2 mode to alternate function type*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*set PA2 alternate function type to AF07(UART_TX)*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*set PA3 to alternate function type*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*set PA3 alternate function type to AF07*/
	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);


	/*CONFIGURE THE UART module*/
	/*enable clock access to uart2*/
	RCC->APB1ENR |=USART2EN;

	/*configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BaudRate);


	/*configure transfer direction*/
	USART2->CR1 =(CR1_TE |CR1_RE); // direct putting equal to so that other values are set to their default indicating default mode of action.

	/*enable uart module*/
	USART2->CR1 |=CR1_UE;

	/*Enable RXNE Interrupt*/
	USART2->CR1 |=CR1_RXNEIE;

	/*Enable UART2 interrupt in NVIC*/
	NVIC_EnableIRQ(USART2_IRQn);

}

void uart2_tx_init(void)
{
	/*CONFIGURE UART GPIO PIN*/

	/*enable clock access to GPIOA*/
	RCC->AHB1ENR |=GPIOAEN;

	/*set PA2 mode to alternate function type*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*set PA2 alternate function type to AF07(UART_TX)*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*CONFIGURE THE UART module*/
	/*enable clock access to uart2*/
	RCC->APB1ENR |=USART2EN;

	/*configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BaudRate);


	/*configure transfer direction*/
	USART2->CR1 =CR1_TE; // direct putting equal to so that other values are set to their default indicating default mode of action.

	/*enable uart module*/
	USART2->CR1 |=CR1_UE;

}

void dma_1_stream6_init(uint32_t src,uint32_t dst,uint32_t len)
{
	// enable clock access to DMA
	RCC->AHB1ENR |=DMA1EN;

	// disable dma1 stream 6
	DMA1_Stream6->CR &=~DMA_S_EN;

	// wait until disabled
	while(DMA1_Stream6->CR & DMA_S_EN)
	{}

	// clear all interrupt flags for stream 6
	DMA1->HIFCR |=(1U<<16);
	DMA1->HIFCR |=(1U<<18);
	DMA1->HIFCR |=(1U<<19);
	DMA1->HIFCR |=(1U<<20);
	DMA1->HIFCR |=(1U<<21);

	// set destination buffer
	DMA1_Stream6->PAR=dst;

	// set source buffer
	DMA1_Stream6->M0AR=src;

	// set length
	DMA1_Stream6->NDTR=len;

	// select stream 6 and CH 4
	DMA1_Stream6->CR =CHSEL4;


	// enable memory or peripheral increment -- here we use memory
	DMA1_Stream6->CR |=DMA_MINC;

	// configure the transfer direction
	DMA1_Stream6->CR |=DMA_DIR_MEM_TO_PERIPH;

	 // Enable circular mode
	DMA1_Stream6->CR |= DMA_CIRC;

	// enable a single interrupt(transfer complete )
	DMA1_Stream6->CR |=DMA_TCIE;

	// enable direct mode and disable FIFO
	DMA1_Stream6->FCR =0;

	// enable DMA 1 Stream 6
	DMA1_Stream6->CR|=DMA_S_EN;

	// enable uart2_tx for DMA
	USART2->CR3 |=UART_CR1_DMAT;

	// DMA Interrupt enable
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}

char uart2_read(void)
{
	/*Make sure the receive data register is not empty*/
	while(!(USART2->DR & SR_RXNE))
	{
		// delay
	}
	/*read from the data register*/
	return USART2->DR;
}
void uart2_write(int ch)
{
	/*Make sure the transmit data register is empty*/
	while(!(USART2->SR & SR_TXE))
	{
		// wait until transmit data register is empty we can write to data register
	}

	/*Write to transmit data register*/
	USART2->DR=(ch & 0xFF); // this means (ch & 11111111 ) and data register is 8 bits for storage

}
static void uart_set_baudrate(USART_TypeDef * USARTx,uint32_t PeriphClk,uint32_t BaudRate)// we will make this compatible with any uart module
{
	USARTx->BRR=compute_uart_bd(PeriphClk,BaudRate);//since only 16 bits are rw in BRR therefore we set reuturn type of comput_uart_bd to uint16_t;
}
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate)
{
	return ((PeriphClk +(BaudRate/2U))/BaudRate);
}
