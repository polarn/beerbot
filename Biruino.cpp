/*
  Biruino.h - Library for Biruinos
*/

#include "Biruino.h"

Biruino BiruinoHandler;

using namespace std;

Biruino::Biruino() {}

void Biruino::init(int pin) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  while (!Serial);
  Serial.print("Serial setup done.");

  Timer1.attachInterrupt(staticCallback);
  Timer1.initialize(100000);
}

// Never use Serial inside the callback or any methods we're calling from there
void Biruino::staticCallback() {
  if (BiruinoHandler.ledFrequencyCounter > BiruinoHandler.ledFrequency) {
    BiruinoHandler.toggleLed();
    BiruinoHandler.ledFrequencyCounter = 0;
  } else {
    BiruinoHandler.ledFrequencyCounter++;
  }
}

void Biruino::toggleLed() {
  if (ledState == 0) {
    digitalWrite(ledPin, HIGH);
    ledState = 1;
  } else {
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }
}

void Biruino::blinkSlow() {
  ledFrequency = BIRUINO_BLINK_SLOW_TICKS;
}

void Biruino::blinkFast() {
  ledFrequency = BIRUINO_BLINK_FAST_TICKS;
}

void Biruino::blinkNormal() {
  ledFrequency = BIRUINO_BLINK_NORMAL_TICKS;
}

void Biruino::randomSleep() {
  int randomSleep = random(20);
  Serial.println();
  Serial.print("Will sleep for ");
  Serial.print(randomSleep);
  Serial.print(" seconds: ");

  blinkSlow();
  for (int i = 0; i < randomSleep; i++) {
    Serial.print(".");
    delay(1000);
  }

  blinkNormal();
  Serial.println();
}
