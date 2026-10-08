#include "uart.h"

#define GPIOAEN			(1U << 0)
#define UART2EN			(1U << 17)

#define CR1_TE			(1U << 3)
#define CR1_RE			(1U << 2)
#define CR1_UE			(1U << 13)

#define SR_RXNE			(1U << 5)
#define SR_TXE			(1U << 7)

#define SYS_FREQ		16000000
#define APB1_CLK		(SYS_FREQ)

#define UART_BAUDRATE	115200

void uart2_write(int ch);
int __io_putchar(int ch);

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate);

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uart2_rxtx_init(void){
	/*********Configuration UART GPIO PIN*********/
	/*1.Enable clock access to gpio*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA2 mode to alternate function mode*/
	/*Set PA2 alternate function to type to UART_TX (AF7)*/
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	/*3.Set PA3 mode to alternate function mode*/
	/*Set PA3 alternate function to type to UART_RX (AF7)*/
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);

	GPIOA->AFR[0] |= (1U << 12);
	GPIOA->AFR[0] |= (1U << 13);
	GPIOA->AFR[0] |= (1U << 14);
	GPIOA->AFR[0] &= ~(1U << 15);

	/*********Configuration UART Module*********/
	/*1.Enable clock access to UART2*/
	RCC->APB1ENR |= UART2EN;

	/*2.Config baudrate UART2*/
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*3.Config the transfer direction*/
	/*TE: Transmit enable; RE: Receiver enable*/
	USART2->CR1 = (CR1_TE | CR1_RE);

	// USART2->CR2: no need config because 00 -> 1 bit stop
	// Parity Selection: even parity --> 00

	/*4. Enable UART*/
	/*UE: USART enable*/
	USART2->CR1 |= CR1_UE;
}

char uart2_read(void){
	/*Make sure the data transmit register is not empty*/
	while(!(USART2->SR & SR_RXNE));
	return USART2->DR;

}

void uart2_write(int ch){
	/*Make sure the data transmit register empty*/
	while (!(USART2->SR & SR_TXE));
	USART2->DR = (ch & 0xFF);

}

static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}


