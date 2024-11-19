/*
 * keypad.h
 *
 * Created: 2024-11-15 오후 9:56:51
 *  Author: james
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>

//define microcontroller pins connected to SN74HC165

#define SHIFT_DATA_PIN	PINB0 //Q7 Serial Data Output
#define SHIFT_CLOCK_PIN	PINB1 //clk
#define SHIFT_LOAD_PIN	PINB2 //PL* (async Parallel Load in)

//Port Definitions
#define SHIFT_PORT		PORTB
#define SHIFT_PIN		PINB
#define SHIFT_DDR		DDRB

void keypad_init(void);
char keypad_get_debounced_key(void);

#endif /* KEYPAD_H_ */