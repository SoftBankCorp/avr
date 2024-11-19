#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define ubbr F_CPU/16/BAUD-1

void USART_Init(unsigned int baud);
void USART_Send_Char(char data);
void USART_Print(char *str);

#endif // UART_H
