/*
 * us.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#ifndef US_H_
#define US_H_

#include "state.h"

enum {
	US_busy
}US_state_id;

STATE_define(US_busy);

void US_init();
int US_get_distance_random(int l , int r , int count);

extern void (* US_state)();


#endif /* US_H_ */
