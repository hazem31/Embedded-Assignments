/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */




#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SET_BIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define RESET_BIT(ADDRESS,BIT) (ADDRESS &= (~(1<<BIT)))
#define TOGGLE_BIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define READ_BIT(ADDRESS,BIT) (ADDRESS & ((1<<BIT)>>BIT) )


int main()
{
	// make portD pins 5,6,7 output
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);

	// INT0 External is logical change
	SET_BIT(MCUCR,0);
	RESET_BIT(MCUCR,1);

	// INT1 External is Rising change
	SET_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);

	// INT2 External is Falling change
	RESET_BIT(MCUCSR,6);

	// Enable interrupts
	SET_BIT(GICR,5);
	SET_BIT(GICR,6);
	SET_BIT(GICR,7);

	// enable global interrupt
	SET_BIT(SREG,7);

	while(1)
	{
		RESET_BIT(PORTD,5);
		RESET_BIT(PORTD,6);
		RESET_BIT(PORTD,7);
	}

	return 0;
}

ISR(INT0_vect) {
	SET_BIT(PORTD,5);
	_delay_ms(1000);

}

ISR(INT1_vect) {
	SET_BIT(PORTD,6);
	_delay_ms(1000);
}

ISR(INT2_vect) {
	SET_BIT(PORTD,7);
	_delay_ms(1000);
}

