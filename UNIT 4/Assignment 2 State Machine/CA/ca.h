/*
 * ca.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#ifndef CA_H_
#define CA_H_
#include "state.h"

enum {
	CA_waiting,
	CA_driving
}CA_state_id;

STATE_define(CA_waiting);
STATE_define(CA_driving);

extern void (* CA_state)();

int US_get_distance_random(int l , int r , int count);

#endif /* CA_H_ */
