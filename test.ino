/*
  Test
 */

#include <Arduino.h>

#include "Biruino.h"

Biruino biruino(LED_BUILTIN, 1000);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting...");
  biruino.start();
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
