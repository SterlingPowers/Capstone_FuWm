/*
 * Project Capstone
 * Author: Sterling Powers
 * Date: 04-09-25
 */

 #include "Particle.h"
 #include "MP3_CNM.h"
 #include "Button.h"
 #include "Adafruit_GFX.h"

 
 Button nextButton(S3);  
 DFRobotDFPlayerMini thePlayer;
 const int diode1=A2;
 const int diode2=A1;
 const int diode3=A0;
 const int laser1=A5;
 const int laser2=S4;
 const int laser3=S3;

 const int lightThreshold = 3000;
 bool leftBeamPreviouslyIntact = true;
 bool rightBeamPreviouslyIntact = true;
 
 SYSTEM_MODE(SEMI_AUTOMATIC);
 
 void setup() {
  pinMode (laser1, OUTPUT);
  pinMode (laser2, OUTPUT);
  pinMode (laser3, OUTPUT);
  pinMode (diode1, INPUT);
  pinMode (diode2, INPUT);
  pinMode (diode3, INPUT);

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
   thePlayer.enableLoopAll ();

 }
 
 void loop() {
  digitalWrite (laser1, HIGH);
  digitalWrite (laser2, HIGH);
  digitalWrite (laser3, HIGH);
  delay (100);

  int sensorValue1 = analogRead (diode1);
  Serial.printf("Left: %d\n", sensorValue1);
  int sensorValue2 = analogRead (diode2);
  Serial.printf("Center: %d\n", sensorValue2);
  int sensorValue3 = analogRead (diode3);
  Serial.printf("Right: %d\n", sensorValue3);

  bool leftBeamIsBroken = sensorValue1<lightThreshold;
  bool rightBeamIsBroken = sensorValue3<lightThreshold;

  if (leftBeamIsBroken && leftBeamPreviouslyIntact) {
     Serial.println("Previous Song");
     thePlayer.previous();
     thePlayer.previous();
   }
   leftBeamPreviouslyIntact =!leftBeamIsBroken;

   if (rightBeamIsBroken && rightBeamPreviouslyIntact) {
    Serial.println("Next Song");
    thePlayer.next();
    thePlayer.next();
  }
  rightBeamPreviouslyIntact =!rightBeamIsBroken;
}

 
 