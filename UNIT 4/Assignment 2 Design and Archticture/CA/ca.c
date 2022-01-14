/*
 * ca.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */
#include "ca.h"

int CA_speed= 0;
int CA_distance = 0;
int CA_threshold = 50;

void (* CA_state)();

void US_distance_f(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving)) ;
	printf("US --------distance = %d ---------> CA\n",d);
}

STATE_define(CA_waiting) {

	CA_state_id = CA_waiting;
	//action
	CA_speed = 0;
	DC_speed_f(CA_speed);
	//event_check
	printf("CA_waiting state : distance = %d speed=%d \n",CA_distance,CA_speed);
}

STATE_define(CA_driving) {

	CA_state_id = CA_driving;

	//action
	CA_speed = 30;
	DC_speed_f(CA_speed);
	//event_check
	printf("CA_driving state : distance = %d speed=%d \n",CA_distance,CA_speed);
}

