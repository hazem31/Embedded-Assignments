

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include"state.h"


enum {
    PC_idle,
    PC_busy
}PC_state_id;

extern void (*PC_state)();

STATE_define(PC_idle);
STATE_define(PC_busy);

#endif