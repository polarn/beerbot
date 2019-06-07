/*
  Test
 */

#include <Arduino.h>

#include "Biruino.h"

void setup() {
  BiruinoHandler.init(LED_BUILTIN);
}

void loop() {
  Serial.println("blinkNormal...");
  BiruinoHandler.blinkNormal();
  delay(10000);
  Serial.println("blinkFast...");
  BiruinoHandler.blinkFast();
  delay(10000);
  Serial.println("blinkSlow...");
  BiruinoHandler.blinkSlow();
  delay(10000);
}
