/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */


#include "ca.h"
#include "us.h"
#include "dc.h"

void setup()
{
	DC_init();
	US_init();
	CA_state = STATE(CA_waiting);
	DC_state = STATE(DC_idle);
	US_state = STATE(US_busy);
}

void main()
{
	volatile int d;
	setup();
	while(1)
	{
		US_state();
		CA_state();
		DC_state();

		for(d = 0 ; d <= 1000 ; d++);
	}
}
