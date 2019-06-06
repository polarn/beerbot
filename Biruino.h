/*
  Biruino.h - Library for Biruinos
*/
#ifndef Biruino_h
#define Biruino_h

#include <TimerOne.h>

#define BIRUINO_BLINK_SLOW_TICKS 100
#define BIRUINO_BLINK_NORMAL_TICKS 25
#define BIRUINO_BLINK_FAST_TICKS 5

class Biruino {
  public:
    Biruino();
    void init(int pin);
    static void staticCallback();
    void callback();
    void toggleLed();
    void blinkSlow();
    void blinkFast();
    void blinkNormal();
    void randomSleep();
  private:
    int ledPin;
    int ledState;
    int ledFrequencyCounter;
    int ledFrequency;
  };

extern Biruino BiruinoHandler;

#endif
