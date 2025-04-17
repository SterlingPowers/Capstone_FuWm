#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

// For WS2812B LED strip on pin D5
const int PIXEL_PIN = D5;
const int PIXEL_COUNT = 8;
const int BRIGHTNESS = 50;

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, WS2812B);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Start with all off

  Serial.begin(9600);
  waitFor(Serial.isConnected, 5000);
  Serial.println("NeoPixel test started");
}

void loop() {
  // Cycle through Red, Green, Blue, Warm White
  colorWipe(strip.Color(255, 0, 0), "Red");
  colorWipe(strip.Color(0, 255, 0), "Green");
  colorWipe(strip.Color(0, 0, 255), "Blue");
  colorWipe(strip.Color(255, 147, 41), "Warm White");
  colorWipe(strip.Color(0, 0, 0), "Off");
}

void colorWipe(uint32_t color, const char* label) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  Serial.println(label);
  delay(1000);
}
