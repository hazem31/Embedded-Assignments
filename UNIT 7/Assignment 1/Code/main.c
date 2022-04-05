/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */




//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>

#include "address.h"

#define F_CPU 8000000UL

#define SET_BIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define RESET_BIT(ADDRESS,BIT) (ADDRESS &= (~(1<<BIT)))
#define TOGGLE_BIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define READ_BIT(ADDRESS,BIT) ( ( ADDRESS & (1<<BIT) )>>BIT) )

void wait_ms(unsigned char time)
{
	unsigned int i , j;
	for(i = 0 ; i < time ; i++)
		for(j = 0 ; j < 10000 ; j++);
}

int main()
{

	DDRD |= 0b11110000;
	while(1)
	{
		PORTD = 0b10000000;
		wait_ms(20);
		PORTD = 0b01000000;
		wait_ms(20);
		PORTD = 0b00100000;
		wait_ms(20);
		PORTD = 0b00010000;
		wait_ms(20);
	}

	return 0;
}
