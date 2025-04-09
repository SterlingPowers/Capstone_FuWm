#include "Particle.h"

#define LEFT_PIN D7
#define RIGHT_PIN D8
#define TONE_FREQ 1000         // Hz
#define HALF_PERIOD_MICROS 500 // 1000Hz = 500us high, 500us low

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("🔊 Software square wave test");

  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LEFT_PIN, HIGH);
  digitalWrite(RIGHT_PIN, HIGH);
  delayMicroseconds(HALF_PERIOD_MICROS);

  digitalWrite(LEFT_PIN, LOW);
  digitalWrite(RIGHT_PIN, LOW);
  delayMicroseconds(HALF_PERIOD_MICROS);
}
