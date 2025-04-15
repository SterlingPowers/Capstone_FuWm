#include <SPI.h>
#include "Adafruit_GFX.h"
#include "GC9A01A.h"

// Define pins
#define TFT_CS   D7
#define TFT_DC   D5
#define TFT_RST  D6

// Set up display instance
GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  delay(1000);
  Serial.println("Initializing display...");

  // Start the display
  tft.begin();
  tft.setRotation(0); // 0–3 for different orientations

  // Fill screen with a color
  tft.fillScreen(GC9A01A_BLUE);
  
  // Draw some text
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 120);
  tft.print("Hello, Photon2!");
}

void loop() {
  // nothing for now
}
