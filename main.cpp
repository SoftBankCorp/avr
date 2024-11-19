/*
 * 4_4keypad_w_165.cpp
 *
 * Created: 2024-11-15 오후 9:54:58
 * Author : james
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "keypad.h"


int main(void)
{
	
	USART_Init(ubbr);
	USART_Print("UART Initialized\r\n");
    char key;
	keypad_init();
	
	//init UART
	
    while (1)
    {
		key = keypad_get_debounced_key();
		if(key!='\0'){
			USART_Send_Char(key);
		}
    }
}

