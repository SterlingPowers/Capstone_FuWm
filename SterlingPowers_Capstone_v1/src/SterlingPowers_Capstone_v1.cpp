/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Encoder.h"
#include <SPI.h>
#include "SdFat.h"


const int SD_CS (D4); //card select
const int PCM_BCK (D2); //bit clock
const int PCM_LCK (D3); //mono/left channel select
const int PCM_DIN (D1); //serial data in

SdFat sd;
File audioFile;

Encoder myEnc(D15,D16);

int pos, lastPos;

SYSTEM_MODE(SEMI_AUTOMATIC);

//write 1 bit at a time (MSB first)
void sendBit(bool bit) {
  digitalWrite(PCM_DIN, bit);
  digitalWrite(PCM_BCK, HIGH);
  delay (1);
  digitalWrite(PCM_BCK, LOW);
  delay (1);
}
//send 16-bit sample over I2S (left-justified, 32-bit word)
void sendI2SSample(int16_t sample) {
  digitalWrite(PCM_LCK, LOW);  // Left channel (mono)

  for (int i = 15; i >= 0; i--) {
    sendBit((sample >> i) & 0x01);
  }

  // Pad remaining 16 bits (to complete 32-bit word)
  for (int i = 0; i < 16; i++) {
    sendBit(0);
  }

  // Optional: right channel (repeat mono sample)
  digitalWrite(PCM_LCK, HIGH);
  for (int i = 15; i >= 0; i--) {
    sendBit((sample >> i) & 0x01);
  }

  for (int i = 0; i < 16; i++) {
    sendBit(0);
  }
}

void setup() {
  Serial.begin (9600);
  delay (2000);
  Serial.println ("Initializing");
  sd.begin ();

  //set I2S pins as output
  pinMode (PCM_BCK, OUTPUT);
  pinMode (PCM_LCK, OUTPUT);
  pinMode (PCM_DIN, OUTPUT);

  digitalWrite (PCM_BCK, LOW);
  digitalWrite (PCM_LCK, LOW);
  digitalWrite (PCM_DIN, LOW);

  //mount SD card
  sd.begin (SD_CS);
  if (!sd.begin(SD_CS)){
    Serial.println ("card mount failed");
    return;
  }
  Serial.println ("Card Mounted");

  //open Wav file
  audioFile = sd.open ("/01HTL.wav", FILE_READ);
  if (!audioFile){
    Serial.println ("failed to open file");
    return;
  }
  // Skip 44-byte header
  audioFile.seek(44);
  Serial.println("Playing WAV via I2S...");
}


void loop() {
  static uint8_t buffer[512];

  if (!audioFile.available()) {
    audioFile.close();
    Serial.println("Playback complete.");
    while (1);
  }

  int bytesRead = audioFile.read(buffer, sizeof(buffer));

  for (int i = 0; i < bytesRead; i += 2) {
    if (i + 1 >= bytesRead) break;

    // Combine two bytes into 16-bit sample
    int16_t sample = buffer[i] | (buffer[i + 1] << 8);

    // Send to DAC
    sendI2SSample(sample);

    // Wait ~22kHz sample rate (adjust this as needed)
    delay(45);  // Tune for actual sample rate!
  }
  // pos = myEnc.read();
  // if(pos != lastPos) {
  //   Serial.printf("Encoder position = %i\n",pos);
  // }
  // lastPos = pos;
}
