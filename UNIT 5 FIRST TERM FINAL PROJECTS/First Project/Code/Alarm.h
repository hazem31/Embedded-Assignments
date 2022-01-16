
#ifndef _ALARM_H_
#define _ALARM_H_

#include "state.h"
#include "driver.h"



enum {
    AL_idle,
    AL_busy
}AL_state_id;


extern void (*AL_state)();

STATE_define(AL_idle);
STATE_define(AL_busy);



#endif