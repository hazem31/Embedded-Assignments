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
		for(j = 0 ; j < 100 ; j++);
}

int main()
{
	unsigned char i,j,k;
	DDRC |= 0b11111100;
	while(1)
	{
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				for(k = 0 ; k < 100 ; k++)
				{
					PORTC = (i<<4) | (0b1000);
					wait_ms(1);
					PORTC = (j<<4) | (0b0100);
					wait_ms(1);
				}
			}
		}
	}

	return 0;
}
