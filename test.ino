/*
  Test
 */

#include <Arduino.h>

#include "Biruino.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  BiruinoHandler.init(LED_BUILTIN);
}

void loop() {
  Serial.println("Loop...");
  delay(3000);
}
