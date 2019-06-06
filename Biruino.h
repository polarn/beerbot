/*
  Biruino.h - Library for Biruinos
*/
#ifndef Biruino_h
#define Biruino_h

#include <TimerOne.h>

class Biruino {
  public:
    Biruino();
    void init(int led);
    static void staticCallback();
    void callback();
  private:
    int _pin;
    int _ledState;
  };

extern Biruino BiruinoHandler;

#endif
