#include "uart.h"

void USART_Init(unsigned int baud)
{
	unsigned int ubrr = F_CPU/16/baud -1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L=(unsigned char)ubrr;
	UCSR0B = (1<< TXEN0) | (1<<RXEN0); //송수신 활성화
	UCSR0C = (1<< UCSZ01)| (1<<UCSZ00); //8bit data, no parity,1 stop bit
}

void USART_Send_Char(char data){
	while (!(UCSR0A &  (1<<UDRE0))); //Wait for empty ransmit buffer
	UDR0 = data;
}

void USART_Print(char *str)
{
	while (*str)
	{
		USART_Send_Char(*str++);
	}
}
