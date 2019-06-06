/*
  Test
 */

#include <Arduino.h>

#include "Biruino.h"

void setup() {
  BiruinoHandler.init(LED_BUILTIN);
}

void loop() {
  Serial.println("Loop...");
  BiruinoHandler.blinkSlow();
  delay(5000);
  //BiruinoHandler.blinkNormal();
  delay(5000);
  //BiruinoHandler.blinkFast();
  delay(5000);
}
