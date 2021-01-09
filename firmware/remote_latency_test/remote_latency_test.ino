//-*- c++ -*-
#include <radio.h>
#include "quad_remote.h"
#include "ControlState.h"
#include "MenuItem.hpp"

void setup() {
  const int RADIO_CHANNEL = 23;        // Channel for radio communications (can be 11-26)
  const int SERIAL_BAUD = 9600;        // Baud rate for serial port

  Serial.begin(SERIAL_BAUD);           // Start up serial
  quad_remote_setup();
  analogReference(INTERNAL);
  rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel
 
}
void loop() {
  int value = analogRead(PIN_THROTTLE);
#if(0)
  constrain(map(analogRead(PIN_THROTTLE),
            0, 1024,
            0, 255),  
              0, 255); 
#endif    
  rfWrite((uint8_t*)&value, sizeof(value));
  Serial.println(value);
}
