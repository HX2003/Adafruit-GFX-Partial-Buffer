
#include "Adafruit_GFX.h"

class PartialBuffer : public Adafruit_GFX {
 public:
  PartialBuffer(uint16_t width, uint16_t height);
  void
    drawPixel(int16_t x, int16_t y, uint16_t c),
    writePixel(int16_t x, int16_t y, uint16_t c),
	writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t c),
	writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c),
	writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c),
	fillScreen(uint16_t c);
  uint16_t *bufferOut(void);
  uint16_t pixelOut(int16_t x, int16_t y);
 private:
  uint16_t *buffer;
  uint16_t width;
  uint16_t height;
}; 