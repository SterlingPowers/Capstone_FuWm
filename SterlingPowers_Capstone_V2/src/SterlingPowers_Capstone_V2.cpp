/*
 * Project Capstone
 * Author: Sterling Powers
 * Date: 04-09-25
 */

 #include "Particle.h"
 #include "MP3_CNM.h"
 #include "Button.h"
 
 Button nextButton(A5);  // A5 connected to button, other side to GND
 DFRobotDFPlayerMini thePlayer;
 
 SYSTEM_MODE(SEMI_AUTOMATIC);
 
 void setup() {
   Serial.begin(9600);
   waitFor(Serial.isConnected, 1000);
   Serial1.begin(9600);
   delay(1000);
 
   Serial.println("Welcome to FuWm");
   Serial.println("About to init DFPlayer...");
   
   if (!thePlayer.begin(Serial1)) {
     Serial.println("Hold up. I'm having issues...");
     while (true);
   }
   Serial.println("Let's Go");
 
   thePlayer.volume(30);  // Range: 0–30
   thePlayer.play(1);     // Starts with track 1
 }
 
 void loop() {
   if (nextButton.isClicked()) {
     Serial.println("Next Song");
     thePlayer.next();
   }
 }
 