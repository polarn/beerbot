/*
  Test
 */

#include <Arduino.h>

#include "Biruino.h"

// Biruino biruino(LED_BUILTIN, 1000);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  BiruinoHandler.init(LED_BUILTIN);
}

void loop() {
  Serial.println("Loop...");
  /*
  biruino.dot(); biruino.dot(); biruino.dot();
  biruino.dash(); biruino.dash(); biruino.dash();
  biruino.dot(); biruino.dot(); biruino.dot();
  */
  delay(3000);
}
