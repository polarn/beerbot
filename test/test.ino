
/*
  Test
 */

#define BIRUINO_NAME "test"
#define BIRUINO_PUBNUB_CHANNEL_PING "ping"
#define BIRUINO_PUBNUB_CHANNEL_SEND "test"

#include <Arduino.h>
#include "Biruino.h"

void setup() {
  BiruinoHandler.init(LED_BUILTIN, BIRUINO_NAME, BIRUINO_PUBNUB_CHANNEL_SEND, BIRUINO_PUBNUB_CHANNEL_PING);
}

void loop() {
  BiruinoHandler.runFromLoop();
}
