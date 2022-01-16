
#include "Alarm.h"

static unsigned int duration = 0;

void (*AL_state)();

STATE_define(AL_idle) {
    
    AL_state_id = AL_idle;
    duration = 0;
    Set_Alarm_actuator(1);
    

}

void SetTimer(int t) {
    
    duration = t;
    AL_state = STATE(AL_busy);
}

STATE_define(AL_busy) {
    
    AL_state_id = AL_busy;
    Set_Alarm_actuator(duration);
    if (duration == 0)
    {
        Delay(1000000);
        duration = 1;
    }
    AL_state = STATE(AL_idle);
    

}
