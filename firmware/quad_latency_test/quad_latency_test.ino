//-*- c++ -*-
#include <radio.h>

void setup() {
  const int RADIO_CHANNEL = 23;        // Channel for radio communications (can be 11-26)
  const int SERIAL_BAUD = 9600;        // Baud rate for serial port

  Serial.begin(SERIAL_BAUD);           // Start up serial
  rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel 
}
void loop() {
  int value;
  if (rfRead((uint8_t*)&value, sizeof(value)) == sizeof(value)) {
    Serial.println(value); 
    analogWrite(4, value/4);
  } else {
  }
}
