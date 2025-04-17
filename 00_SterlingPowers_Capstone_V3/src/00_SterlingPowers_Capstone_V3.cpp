/*
 * Project Capstone + Sonic Volume Control (Center Beam)
 * Author: Sterling Powers
 * Date: 04-16-25
 */

 #include "Particle.h"
 #include "MP3_CNM.h"
 #include "Adafruit_GFX.h"
 #include "neopixel.h"
 
 class Button {
   int _buttonPin;
   int _prevButtonState;
   bool _pullUp;
 
 public:
   Button(int buttonPin, bool pullUp = false) {
     _buttonPin = buttonPin;
     _pullUp = pullUp;
 
     if (_pullUp) {
       pinMode(_buttonPin, INPUT_PULLUP);
     } else {
       pinMode(_buttonPin, INPUT_PULLDOWN);
     }
 
     _prevButtonState = _pullUp ? 1 : 0;
   }
 
   bool isPressed() {
     bool _buttonState = digitalRead(_buttonPin);
     if (_pullUp) {
       _buttonState = !_buttonState;
     }
     return _buttonState;
   }
 
   bool isClicked() {
     bool _buttonState = digitalRead(_buttonPin);
     if (_pullUp) {
       _buttonState = !_buttonState;
     }
     bool _clicked = (_buttonState != _prevButtonState) ? _buttonState : false;
     _prevButtonState = _buttonState;
     return _clicked;
   }
 };

 #define TRIG_PIN D7
 #define ECHO_PIN D6
 
 Button powerButton(S3);  
 DFRobotDFPlayerMini thePlayer;
 
 const int diode1 = A0;  // Left beam
 const int diode2 = A1;  // Center beam (volume control)
 const int diode3 = A2;  // Right beam

const int PIXELCOUNT = 8;
const int PIXELDELAY = 50;
int i,r,g,b;

Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
 
 const int lightThreshold = 1000;
 
 bool leftBeamPreviouslyIntact = true;
 bool centerBeamPreviouslyIntact = true;
 bool rightBeamPreviouslyIntact = true;
 
 bool systemIsOn = false;
 bool isPlaying = false;
 
 int lockedVolume = 20;  // Initial volume setting
 
 SYSTEM_MODE(SEMI_AUTOMATIC);
 
 // Custom pulseIn for Photon2
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
   pinMode(diode1, INPUT);
   pinMode(diode2, INPUT);
   pinMode(diode3, INPUT);
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);

  pixel.begin();
  pixel.setBrightness(31);
  pixel.show();

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
 
   Serial.println("DFPlayer ready.");
   thePlayer.volume(lockedVolume);
   thePlayer.pause(); // Start in paused/off state
 }
 
 void loop() {
   if (powerButton.isClicked()) {
     systemIsOn = !systemIsOn;
     if (systemIsOn) {
       Serial.println("System ON");
       thePlayer.play(1);
       thePlayer.enableLoopAll();
       isPlaying = true;

  // Light all pixels warm white
  for (int i = 0; i < PIXELCOUNT; i++) {
    pixel.setPixelColor(i, pixel.Color(255, 147, 41)); // Warm white
  }
  pixel.show();

     } else {
       Serial.println("System OFF");
       thePlayer.pause();
       isPlaying = false;

       pixel.clear();
       pixel.show();
     }
     delay(300); // basic debounce
   }
 
   if (!systemIsOn) return;
 
   // Read photo diodes
   int sensorValue1 = analogRead(diode1);  // Left
   int sensorValue2 = analogRead(diode2);  // Center
   int sensorValue3 = analogRead(diode3);  // Right
   Serial.printf("Left: %d | Center: %d | Right: %d\n", sensorValue1, sensorValue2, sensorValue3);
 
   bool leftBeamIsBroken = sensorValue1 < lightThreshold;
   bool centerBeamIsBroken = sensorValue2 < lightThreshold;
   bool rightBeamIsBroken = sensorValue3 < lightThreshold;
 
   // Handle previous track (left beam)
   if (leftBeamIsBroken && leftBeamPreviouslyIntact) {
     Serial.println("Previous Song");
     thePlayer.previous();
   }
   leftBeamPreviouslyIntact = !leftBeamIsBroken;
 
   // Handle play/pause toggle (right beam)
   if (rightBeamIsBroken && rightBeamPreviouslyIntact) {
     isPlaying = !isPlaying;
     if (isPlaying) {
       Serial.println("Play");
       thePlayer.start();
     } else {
       Serial.println("Pause");
       thePlayer.pause();
     }
   }
   rightBeamPreviouslyIntact = !rightBeamIsBroken;
 
   // Handle volume control (center beam)
   if (centerBeamIsBroken) {
     // Trigger ultrasonic reading
     digitalWrite(TRIG_PIN, LOW);
     delayMicroseconds(2);
     digitalWrite(TRIG_PIN, HIGH);
     delayMicroseconds(10);
     digitalWrite(TRIG_PIN, LOW);
 
     long duration_us = pulseIn1(ECHO_PIN, HIGH);
     if (duration_us > 0) {
       float distance_cm = (duration_us * 0.0343) / 2.0;
       int volume = map((int)distance_cm, 5, 50, 30, 5);
       volume = constrain(volume, 0, 30);
 
       if (volume != lockedVolume) {
         Serial.printf("Setting volume: %d (distance: %.2f cm)\n", volume, distance_cm);
         thePlayer.volume(volume);
         lockedVolume = volume;
       }
     } else {
       Serial.println("No ultrasonic pulse detected");
     }
   }
 
   if (!centerBeamIsBroken && centerBeamPreviouslyIntact == false) {
     Serial.printf("Center beam restored — volume locked at: %d\n", lockedVolume);
   }
   centerBeamPreviouslyIntact = !centerBeamIsBroken;
 
   delay(300);
 }
 