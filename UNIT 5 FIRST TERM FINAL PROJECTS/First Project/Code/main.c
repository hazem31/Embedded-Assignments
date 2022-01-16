#include <stdint.h>
#include <stdio.h>

#include "driver.h"
#include "Sensor.h"
#include "Alarm.h"
#include "Controller.h"

int main (){
	GPIO_INITIALIZATION();
	PC_state = STATE(PC_idle);
	AL_state = STATE(AL_idle);
	PS_state = STATE(PS_idle);
	while (1)
	{
		PS_state();
		PC_state();
		AL_state();
	}

}
