/*
  Biruino.h - Library for Biruinos
*/
#ifndef Biruino_h
#define Biruino_h

#include <Timer.h>

class Biruino {
  public:
    Biruino(int pin, long timeout);
    void start();
    static void staticCallback(void *context);
    void callback();
    void dot();
    void dash();
  private:
    Timer *_timer;
    int _pin;
    int _ledState;
    long _defaultBlinkTimeout;
    int _event;
  };

void cb();

#endif
