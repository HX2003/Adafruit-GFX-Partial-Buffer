# Adafruit-GFX-Partial-Buffer
Create a virtual buffer which can be modified just like a real display. Works only for 16 bit colour mode. Useful to prevent flickering when updating text for a small section of display.
# Getting started
In your sketch include this library

`#include <PartialBuffer.h>`

Instantiate the buffer with a width of 320 pixels and height of 16 pixels for example.

`PartialBuffer myBuffer(320, 16);`

Next, you can use Adafruit GFX functions to modify your buffer, for example

`myBuffer.fillScreen(0x0000);`

To retrieve the data for a pixel at (8, 15)

`myBuffer.getPixel(8, 15);`

To retrieve the entire buffer

`myBuffer.getBuffer();`

# Limitations
× Take note of memory usage
