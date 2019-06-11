/*
  Biruino.h - Library for Biruinos
*/
#ifndef Biruino_h
#define Biruino_h

#include <Ticker.h>
#include <Arduino.h>
#include "secrets.h"

#define BIRUINO_BLINK_TICK_TIME 0.05
#define BIRUINO_BLINK_SLOW_TICKS 20
#define BIRUINO_BLINK_NORMAL_TICKS 10
#define BIRUINO_BLINK_FAST_TICKS 1
#define BIRUINO_PING_TIMEOUT 30000 // Every 30 second
#define BIRUINO_PING_TICKS 25

#if !defined(BIRUINO_NAME)
#define BIRUINO_NAME "changeme"
#endif

class Biruino {
  public:
    Biruino();
    void init(int _pin, char *_name, char *_channelSend, char *_channelPing);
    static void staticCallback();
    void callback();
    void runFromLoop();
    void toggleLed();
    void blinkSlow();
    void blinkFast();
    void blinkNormal();
    void blinkNotify(int ticks);
    void randomSleep();
    void generateId();
    void sendBoot();
    void sendPing();
    void pubNubPublish(char* msg, const char* chnl);
  private:
    Ticker ticker;
    const char *name;
    const char *channelSend;
    const char *channelPing;
    unsigned long lastPing;
    char id[20];
    volatile int ledPin;
    volatile int ledState;
    volatile int ledFrequencyCounter;
    volatile int ledFrequency;
    volatile int pingFrequencyCounter;
    volatile int pingFrequency;
    volatile int previousLedFrequency;
    volatile int notificationCountdown;
  };

extern Biruino BiruinoHandler;

#endif
