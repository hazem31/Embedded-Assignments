/*
 * us.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#include "us.h"

int US_distance = 0;

void (* US_state)();


STATE_define(US_busy) {

	US_state_id = US_busy;

	//action

	//event_check
	US_distance = US_get_distance_random(44,55,1);

	printf("US_busy state : distance = %d\n",US_distance);

	US_distance_f(US_distance);
	US_state = STATE(US_busy);
}


int US_get_distance_random(int l , int r , int count)
{
	int i;
	for(i = 0 ; i < count ; i++)
	{
		int rand_num = (rand() % (r-l+1)) + l;
		return rand_num;
	}
	return i;
}

void US_init()
{
	printf("US_init \n");
}
