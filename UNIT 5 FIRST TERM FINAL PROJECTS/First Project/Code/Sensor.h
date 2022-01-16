
#ifndef _SENSOR_H_
#define _SENSOR_H_


#include "state.h"
#include "driver.h"



enum {
    PS_idle,
    PS_busy
}PS_state_id;


extern void (*PS_state)();

STATE_define(PS_idle);
STATE_define(PS_busy);



#endif