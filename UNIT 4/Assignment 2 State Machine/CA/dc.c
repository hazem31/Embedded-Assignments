/*
 * dc.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

/*
 * ca.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */
#include "dc.h"

int DC_speed= 0;

void (* DC_state)();

void DC_init()
{
	printf("DC_init\n");
}

void DC_speed_f(int s)
{
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("CA --------speed = %d ---------> DC\n",s);
}

STATE_define(DC_busy) {

	DC_state_id = DC_busy;
	printf("DC_busy state :speed=%d \n",DC_speed);
}

STATE_define(DC_idle) {

	DC_state_id = DC_idle;

	printf("DC_idle state :speed=%d \n",DC_speed);
}


