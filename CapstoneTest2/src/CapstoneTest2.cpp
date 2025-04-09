#include "Particle.h"
#include <SdFat.h>

#define SD_CS A1  // use D4 if you prefer
SdFat sd;
File file;

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("=== SD Read Test — SdFat 1.0.16 ===");

  if (!sd.begin(SD_CS)) {
    Serial.println("❌ SD card init failed.");
    return;
  }

  Serial.println("✅ SD card mounted.");

  file = sd.open("test.txt", FILE_READ);
  if (!file) {
    Serial.println("❌ Couldn't open test.txt");
    return;
  }

  Serial.println("📄 Contents of test.txt:");
  while (file.available()) {
    Serial.write(file.read());
  }

  file.close();
  Serial.println("\n✅ Done reading.");
}

void loop() {}
