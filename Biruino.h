/*
  Biruino.h - Library for Biruinos
*/
#ifndef Biruino_h
#define Biruino_h

#include <TimerOne.h>

#define BIRUINO_BLINK_DELAY 10000
#define BIRUINO_BLINK_SLOW_TICKS 200
#define BIRUINO_BLINK_NORMAL_TICKS 50
#define BIRUINO_BLINK_FAST_TICKS 2

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
