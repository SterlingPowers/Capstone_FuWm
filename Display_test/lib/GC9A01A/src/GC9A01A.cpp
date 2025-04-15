#include "GC9A01A.h"
#include "application.h"
#include "SPI.h"

GC9A01A::GC9A01A(uint8_t cs, uint8_t dc, uint8_t rst)
  : Adafruit_GFX(GC9A01A_TFTWIDTH, GC9A01A_TFTHEIGHT), _cs(cs), _dc(dc), _rst(rst) {}

void GC9A01A::begin() {
  pinMode(_cs, OUTPUT);
  pinMode(_dc, OUTPUT);
  pinMode(_rst, OUTPUT);
  digitalWrite(_cs, HIGH);
  digitalWrite(_dc, HIGH);
  digitalWrite(_rst, HIGH);

  SPI.begin();

  // Reset sequence
  digitalWrite(_rst, LOW);
  delay(20);
  digitalWrite(_rst, HIGH);
  delay(150);

  initDisplay();
}

void GC9A01A::initDisplay() {
  writeCommand(0xEF);
  writeData(0x03);
  writeData(0x80);
  writeData(0x02);

  writeCommand(0x36);
  writeData(0x70);

  writeCommand(0x3A);
  writeData(0x05);

  writeCommand(0xB2);
  writeData(0x0C);
  writeData(0x0C);
  writeData(0x00);
  writeData(0x33);
  writeData(0x33);

  writeCommand(0xB7);
  writeData(0x35);

  writeCommand(0xBB);
  writeData(0x1F);

  writeCommand(0xC0);
  writeData(0x2C);

  writeCommand(0xC2);
  writeData(0x01);

  writeCommand(0xC3);
  writeData(0x0B);

  writeCommand(0xC4);
  writeData(0x20);

  writeCommand(0xC6);
  writeData(0x0F);

  writeCommand(0xD0);
  writeData(0xA4);
  writeData(0xA1);

  writeCommand(0xE0);
  writeData(0xD0);
  writeData(0x04);
  writeData(0x0D);
  writeData(0x11);
  writeData(0x13);
  writeData(0x2B);
  writeData(0x3F);
  writeData(0x54);
  writeData(0x4C);
  writeData(0x18);
  writeData(0x0D);
  writeData(0x0B);
  writeData(0x1F);
  writeData(0x23);

  writeCommand(0xE1);
  writeData(0xD0);
  writeData(0x04);
  writeData(0x0C);
  writeData(0x11);
  writeData(0x13);
  writeData(0x2C);
  writeData(0x3F);
  writeData(0x44);
  writeData(0x51);
  writeData(0x2F);
  writeData(0x1F);
  writeData(0x1F);
  writeData(0x20);
  writeData(0x23);

  writeCommand(0x21); // Inversion on
  writeCommand(0x11); // Sleep out
  delay(120);
  writeCommand(0x29); // Display on
}


void GC9A01A::setRotation(uint8_t r) {
  writeCommand(0x36);
  switch (r % 4) {
    case 0: writeData(0x00); break;
    case 1: writeData(0x60); break;
    case 2: writeData(0xC0); break;
    case 3: writeData(0xA0); break;
  }
}

void GC9A01A::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}

void GC9A01A::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;

  writeCommand(0x2A); // column address set
  writeData(x >> 8);
  writeData(x & 0xFF);
  writeData(x >> 8);
  writeData(x & 0xFF);

  writeCommand(0x2B); // row address set
  writeData(y >> 8);
  writeData(y & 0xFF);
  writeData(y >> 8);
  writeData(y & 0xFF);

  writeCommand(0x2C); // memory write
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  SPI.transfer(color >> 8);   // high byte
  SPI.transfer(color & 0xFF); // low byte
  digitalWrite(_cs, HIGH);
}


void GC9A01A::writeCommand(uint8_t cmd) {
  digitalWrite(_dc, LOW);
  digitalWrite(_cs, LOW);
  SPI.transfer(cmd);
  digitalWrite(_cs, HIGH);
}

void GC9A01A::writeData(uint8_t data) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  SPI.transfer(data);
  digitalWrite(_cs, HIGH);
}
