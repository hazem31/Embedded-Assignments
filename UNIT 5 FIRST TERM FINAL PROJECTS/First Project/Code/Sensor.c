

#include "Sensor.h"

static unsigned int pressure = 0;


void (*PS_state)();

STATE_define(PS_idle) {
    
    PS_state_id = PS_idle;

    pressure = getPressureVal();

    PressureVal(pressure);
    PS_state = STATE(PS_busy);
}

STATE_define(PS_busy) {

    PS_state_id = PS_busy;

    Delay(1000);

    PS_state = STATE(PS_idle);
}