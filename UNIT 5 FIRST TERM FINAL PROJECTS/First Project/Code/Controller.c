
#include"Controller.h"


static unsigned int pressure = 0;
static unsigned int duration = 60;
static unsigned int threshold = 20;

void (*PC_state)();

STATE_define(PC_idle) {

    PC_state_id = PC_idle;
    SetTimer(1);
}

STATE_define(PC_busy) {
    
    PC_state_id = PC_busy;
    if (pressure >= threshold)
    {
        SetTimer(0);
    }
    PC_state = STATE(PC_idle);
    
     
}

void PressureVal(int p) {
    
    pressure = p;
    PC_state = STATE(PC_busy);
}