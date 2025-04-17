/* 
 * Project Sonic Test
 * Author: Sterling Powers
 * Date: 
 */

 #include "Particle.h"

 #define TRIG_PIN D7
 #define ECHO_PIN D6
 
 SYSTEM_MODE(SEMI_AUTOMATIC);
 
 long pulseIn1(uint16_t pin, uint8_t state, unsigned long timeout = 1000000L) {
   unsigned long start = micros();
   while (digitalRead(pin) != state) {
     if (micros() - start > timeout) return 0;
   }
 
   unsigned long pulseStart = micros();
   while (digitalRead(pin) == state) {
     if (micros() - pulseStart > timeout) return 0;
   }
 
   return micros() - pulseStart;
 }
 
 void setup() {
   Serial.begin(9600);
   waitFor(Serial.isConnected, 10000);
 
   delay(2000); 
 
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
 
   Serial.println("HC-SR04 Ready!");
 }
 
 void loop() {
   long duration_us;
   float distance_cm;
 
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
 
   duration_us = pulseIn1(ECHO_PIN, HIGH);
 
   if (duration_us > 0) {
     distance_cm = (duration_us * 0.0343) / 2.0;
     Serial.printf("Distance: %.2f cm\n", distance_cm);
   } else {
     Serial.println("No pulse detected");
   }
 
   delay(500);
 }
 