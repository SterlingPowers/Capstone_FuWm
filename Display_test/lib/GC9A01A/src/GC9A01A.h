#ifndef _GC9A01A_H_
#define _GC9A01A_H_

#include "Adafruit_GFX.h"
#include "application.h"

#define GC9A01A_TFTWIDTH 240
#define GC9A01A_TFTHEIGHT 240

// Color definitions
#define GC9A01A_BLACK   0x0000
#define GC9A01A_BLUE    0x001F
#define GC9A01A_RED     0xF800
#define GC9A01A_GREEN   0x07E0
#define GC9A01A_CYAN    0x07FF
#define GC9A01A_MAGENTA 0xF81F
#define GC9A01A_YELLOW  0xFFE0
#define GC9A01A_WHITE   0xFFFF

class GC9A01A : public Adafruit_GFX {
public:
  GC9A01A(uint8_t cs, uint8_t dc, uint8_t rst);
  void begin();
  void setRotation(uint8_t r);
  void fillScreen(uint16_t color);
  void drawPixel(int16_t x, int16_t y, uint16_t color);

private:
  uint8_t _cs, _dc, _rst;
  void writeCommand(uint8_t cmd);
  void writeData(uint8_t data);
  void initDisplay();
};

#endif
