/*
  Biruino.h - Library for Biruinos
*/

#include "Biruino.h"

Biruino BiruinoHandler;

using namespace std;

Biruino::Biruino() {}

void Biruino::init(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  Timer1.initialize(100000);
}

void Biruino::staticCallback() {
  //BiruinoHandler.callback();
  if (BiruinoHandler._ledState == 0) {
    digitalWrite(BiruinoHandler._pin, HIGH);
    BiruinoHandler._ledState = 1;
  } else {
    digitalWrite(BiruinoHandler._pin, LOW);
    BiruinoHandler._ledState = 0;
  }

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
