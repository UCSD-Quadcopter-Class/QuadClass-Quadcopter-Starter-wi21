#include "ControlState.h"
#include "Arduino.h"

ControlState controls;

void dump_controls()
{
	Serial.print(controls.armed ? "A" : " ");
	Serial.print(" ");
	Serial.print((int)controls.throttle);
	Serial.print(" ");
	Serial.print((int)controls.yaw);
	Serial.print(" ");
	Serial.print((int)controls.pitch);
	Serial.print(" ");
	Serial.print((int)controls.roll);
	Serial.print(" ");
	
	Serial.print((int)controls.tuning);
	Serial.print(" ");

	Serial.print((int)controls.command);
	Serial.print(" ");

	for(int i = 0; i < PID_COUNT; i++) {
		Serial.print(controls.P[i]);
		Serial.print(" ");
		Serial.print(controls.I[i]);
		Serial.print(" ");
		Serial.print(controls.D[i]);
		Serial.print(" ");
		Serial.print(controls.C[i]);
		Serial.print(" ");
		Serial.print((int)controls.trim[i]);
		Serial.print(" ");
	}
	
}


