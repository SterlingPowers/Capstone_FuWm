#include "Particle.h"
#include <SdFat.h>

#define SD_CS A1  // or D4 if you prefer

SdFat sd;

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("=== SD Card Check ===");

  if (!sd.begin(SD_CS, SD_SCK_MHZ(4))) {
    Serial.println("❌ SD card init failed (SPI @ 4 MHz).");
  } else {
    Serial.println("✅ SD card mounted successfully!");
  }
}

void loop() {}
