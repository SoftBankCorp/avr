/*
 * keypad.c
 *
 * Created: 2024-11-15 오후 9:56:39
 *  Author: james
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"

//keypad row pin first 4 lines

const char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void keypad_init(void){ //about shift reg
	//init shift reg interface
	SHIFT_DDR |= (1<< SHIFT_CLOCK_PIN) | (1<< SHIFT_LOAD_PIN);
	SHIFT_DDR &= ~(1 << SHIFT_DATA_PIN); //Input Q7 -> ^Q7
	
	//Enable pull-up resistor on data pin if needed
	//SHIFT_PORT |= (1<< SHIFT_DATA_PIN);
	
	//Initialize clock and load pins
	SHIFT_PORT |= (1<< SHIFT_CLOCK_PIN); //CLK high
	SHIFT_PORT |= (1<< SHIFT_LOAD_PIN); //PL* high
}

uint8_t shift_register_read(void){
	uint8_t data = 0;
	
	//Load parallel data into shift register
	SHIFT_PORT &= ~(1 <<SHIFT_LOAD_PIN); //PL* low
	_delay_us(5); //Short delay
	SHIFT_PORT |= (1 << SHIFT_LOAD_PIN); // PL* high
	
	//Read 8 bits from shift register
	for (uint8_t i=0;i<8;i++)
	{
		
		//Pulse the clock
		SHIFT_PORT &= ~(1 <<SHIFT_CLOCK_PIN);
		_delay_us(1);
		
		//Read data bit
		if (SHIFT_PIN & (1<<SHIFT_DATA_PIN)){
			data |= (1 << (7-i)); //MSB first
		}
		
		SHIFT_PORT |= (1<< SHIFT_CLOCK_PIN); //CLK high
		_delay_us(1);
	}
	
	return data;
}

char keypad_get_key(void){
	uint8_t data = shift_register_read();
	
	uint8_t rows = data&0x0F; //Lower 4bits for rows
	uint8_t cols = (data>>4) & 0x0F; //upper 4 bits for columns
	
	//Since active low, invert bits
	
	rows = ~rows& 0x0F;
	cols= ~cols& 0x0F;
	
	if (rows ==0 || cols ==0){
		return '\0'; //No key pressed
	}
	
	//Find the row index
	uint8_t row_index = 0xFF;
	for(uint8_t i =0 ; i<4; i++){
		if(rows & (1<<i)){
			row_index = i;
			break;
		}
	}
	
	//Find the column index
	uint8_t col_index = 0xFF;
	for (uint8_t i=0;i<4; i++)
	{
		if (cols & (1<<i)){
			col_index = i;
			break;
		}
	}
	
	if (row_index != 0xFF && col_index != 0xff){
		return keypad_map[row_index][col_index];
	}
	
	return '0'; //No valid key detected	
	
}

char keypad_get_debounced_key(void){
	char key1, key2;
	key1 = keypad_get_key();
	if (key1 != '\0'){
		_delay_ms(20); //Debounce delay
		key2 = keypad_get_key();
		if (key1 == key2){
			//wait until key is released
			while( keypad_get_key()!= '\0');
			return key1;
		}
	}
	return '\0';
}