/* 
 * Project Sonic Test
 * Author: Sterling Powers
 * Date: 
 */
#include "Particle.h"

 #define TRIG_PIN A5
 #define ECHO_PIN A2
 
 void setup() {
   Serial.begin(9600);
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
 }
 
 void loop() {
   long duration_us;
   float distance_cm;
 
   // Clear the trigger
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);
 
   // Send 10µs pulse to start measurement
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
 
   // Measure echo duration
   duration_us = pulseIn(ECHO_PIN, HIGH);
 
   // Calculate distance in millimeters
   distance_cm = (duration_us * 0.343) / 58.0;
 
   Serial.print("Distance: ");
   Serial.print(distance_cm);
   Serial.println(" cm");
 
   delay(500);
 }
 