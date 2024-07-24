#include "uart.h"


#define GPIOAEN                     (1U<<0)
#define USART2EN                    (1U<<17)

#define SYS_FREQ        16000000
#define UART_BaudRate   115200
#define APB1_CLK       SYS_FREQ // considering clock tree is not configured. then division factor is 1.

#define CR1_TE      (1U<<3)
#define CR1_UE      (1U<<13)
#define SR_TXE      (1U<<7)
#define CR1_RE      (1U<<2)
#define SR_RXNE     (1U<<5)
#define CR1_RXNEIE  (1U<<5)
#define CR1_TXEIE   (1U<<7)


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

void uart2_tx_interrupt_init(void)//used to enable interrupt.
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

	/*enable interrupt*/
	USART2->CR1 |=CR1_TXEIE;

	/*enable interrupt in NVIC*/
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
