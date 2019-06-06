/*
  Biruino.h - Library for Biruinos
*/

#include "Biruino.h"

using namespace std;

Biruino::Biruino(int pin, long defaultBlinkTimeout) {
  pinMode(pin, OUTPUT);
  _timer = new Timer();
  _pin = pin;
  _defaultBlinkTimeout = defaultBlinkTimeout;
  _ledState = 0;
}

void Biruino::start() {
  Serial.println("Biruino::start()");
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(1000);
  digitalWrite(_pin, HIGH);
  delay(1000);


  _event = _timer->every(_defaultBlinkTimeout, staticCallback, this);
}

void Biruino::staticCallback(void *context) {
  ((Biruino *)context)->callback();
}

void Biruino::callback() {
  if (_ledState == 0) {
    digitalWrite(_pin, HIGH);
    _ledState = 1;
  } else {
    digitalWrite(_pin, LOW);
    _ledState = 0;
  }
}


void Biruino::dot() {
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Biruino::dash() {
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
