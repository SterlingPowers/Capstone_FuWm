/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */
#include "Particle.h"
#include <SdFat.h>

#define SD_CS A1  // Chip select for SD card on SPI (A3/A4/A5)

// Updated PCM5102 pin assignments
#define PCM_DIN D4  // Serial audio data
#define PCM_BCK D5  // Bit clock
#define PCM_LCK D6  // Word clock (Left/Right channel)

SdFat sd;
File audioFile;

void sendBit(bool bit) {
  digitalWrite(PCM_DIN, bit);
  digitalWrite(PCM_BCK, HIGH);
  delayMicroseconds(1);
  digitalWrite(PCM_BCK, LOW);
  delayMicroseconds(1);
}

void sendI2SSample(int16_t sample) {
  // Left channel (mono)
  digitalWrite(PCM_LCK, LOW);
  for (int i = 15; i >= 0; i--) {
    sendBit((sample >> i) & 0x01);
  }
  for (int i = 0; i < 16; i++) sendBit(0); // pad to 32-bit

  // Right channel (copy mono sample)
  digitalWrite(PCM_LCK, HIGH);
  for (int i = 15; i >= 0; i--) {
    sendBit((sample >> i) & 0x01);
  }
  for (int i = 0; i < 16; i++) sendBit(0);
}

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("🎵 WAV Playback Init");

  // Setup output pins for bit-banged I2S
  pinMode(PCM_DIN, OUTPUT);
  pinMode(PCM_BCK, OUTPUT);
  pinMode(PCM_LCK, OUTPUT);
  digitalWrite(PCM_DIN, LOW);
  digitalWrite(PCM_BCK, LOW);
  digitalWrite(PCM_LCK, LOW);

  // Initialize SD card
  if (!sd.begin(SD_CS)) {
    Serial.println("❌ SD card init failed.");
    return;
  }

  Serial.println("✅ SD card mounted.");

  // Open WAV file
  audioFile = sd.open("01HTL.wav", FILE_READ);
  if (!audioFile) {
    Serial.println("❌ Couldn't open 01HTL.wav");
    return;
  }

  // Skip WAV header (usually 44 bytes)
  audioFile.seek(44);
  Serial.println("🎧 Playback started...");
}

void loop() {
  static uint8_t buffer[512];

  if (!audioFile || !audioFile.available()) {
    Serial.println("✅ Playback complete.");
    audioFile.close();
    while (1); // Halt loop
  }

  int bytesRead = audioFile.read(buffer, sizeof(buffer));

  for (int i = 0; i < bytesRead; i += 2) {
    if (i + 1 >= bytesRead) break;

    int16_t sample = buffer[i] | (buffer[i + 1] << 8);
    sendI2SSample(sample);

    // Adjust this for your WAV sample rate
    delayMicroseconds(45); // ~22kHz sample rate
  }
}
