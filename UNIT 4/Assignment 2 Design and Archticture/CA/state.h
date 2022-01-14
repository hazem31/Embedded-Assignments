/*
 * state.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_) ST_##_statFUN_

//connections

void US_distance_f(int d);
void DC_speed_f(int s);

#endif /* STATE_H_ */
