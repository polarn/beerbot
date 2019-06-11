/*
  Biruino.h - Library for Biruinos
*/

#include "Biruino.h"
#include <ESP8266WiFi.h>
#define PubNub_BASE_CLIENT WiFiClient
#define PUBNUB_DEBUG true
#include <PubNub.h>

Biruino BiruinoHandler;

using namespace std;

Biruino::Biruino() {}

void Biruino::init(int _pin, char *_name, char *_channelSend, char *_channelPing) {
  ledPin = _pin;
  name = _name;
  channelSend = _channelSend;
  channelPing = _channelPing;

  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial setup done.");

  Serial.print("Starting Biruino ");
  Serial.println(name);

  ticker.attach(BIRUINO_BLINK_TICK_TIME, staticCallback);

  blinkFast();

  Serial.println("Attempting to connect to network...");

  WiFi.begin(BIRUINO_SSID, BIRUINO_SSID_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  generateId();

  blinkNormal();

  PubNub.begin(BIRUINO_PUBKEY, BIRUINO_SUBKEY);
  PubNub.set_uuid(name);
  Serial.println("PubNub set up");
  Serial.print("Pubnub publish key: ");
  Serial.println(BIRUINO_PUBKEY);
  Serial.print("Pubnub subscribe key: ");
  Serial.println(BIRUINO_SUBKEY);

  sendBoot();
}

void Biruino::runFromLoop() {
  if((millis() - lastPing) > BIRUINO_PING_TIMEOUT) {
    lastPing = millis();
    blinkNotify(BIRUINO_PING_TICKS);
    sendPing();
  }
}

// Never use Serial inside the callback or any methods we're calling from there
void Biruino::staticCallback() {
  if (BiruinoHandler.notificationCountdown > 0) {
    BiruinoHandler.toggleLed();
    BiruinoHandler.notificationCountdown--;
  } else if (BiruinoHandler.ledFrequencyCounter > BiruinoHandler.ledFrequency) {
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

void Biruino::blinkNotify(int ticks) {
  notificationCountdown = ticks;
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

void Biruino::generateId() {
  byte mac[6];
  WiFi.macAddress(mac);
  sprintf(id, "%02X%02X%02X%02X%02X%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  Serial.print("ID (mac address): ");
  Serial.println(id);
}

void Biruino::sendBoot() {
  char message[256];
  sprintf(message, "{\"source\": \"%s\",\"type\": \"boot\",\"uptime\": \"%d\",\"id\": \"%s\"}", name, millis() / 1000, id);
  Serial.print("Sending boot to channel: ");
  Serial.print(channelPing);
  Serial.print(", message: ");
  Serial.println(message);
  pubNubPublish(message, channelPing);
}

void Biruino::sendPing() {
  char message[256];
  sprintf(message, "{\"source\": \"%s\",\"type\": \"ping\",\"uptime\": \"%d\",\"id\": \"%s\"}", name, millis() / 1000, id);
  pubNubPublish(message, channelPing);
}

void Biruino::pubNubPublish(char* msg, const char* chnl) {
  WiFiClient *client;
  
  client = PubNub.publish(chnl, msg);

  if (!client) {
    Serial.println("publishing error");
    delay(1000);
    return;
  }

  if (PubNub.get_last_http_status_code_class() != PubNub::http_scc_success) {
    Serial.print("Got HTTP status code error from PubNub, class: ");
    Serial.print(PubNub.get_last_http_status_code_class(), DEC);
  }

  while (client->available()) {
    Serial.write(client->read());
  }
  client->stop();
  Serial.println("---");
}

