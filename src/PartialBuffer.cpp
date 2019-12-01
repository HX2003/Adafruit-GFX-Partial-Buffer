#include "PartialBuffer.h"

PartialBuffer::PartialBuffer(uint16_t width, uint16_t height) :
  Adafruit_GFX(width, height) {
	this->width = width;
	this->height = height;
    // Allocate and initialize buffer
    uint32_t allocsize  = width * height * 2; //2 bytes for each pixel
    if(NULL == (buffer = (uint16_t *)malloc(allocsize))) return;
    memset(buffer, 0, allocsize);
}
void PartialBuffer::drawPixel(int16_t x, int16_t y, uint16_t c) {
	if((x < 0) || (x >= width) || (y < 0) || (y >= height)) return;  
	buffer[y*width + x] = c;
}
void PartialBuffer::writePixel(int16_t x, int16_t y, uint16_t c) {
	if((x < 0) || (x >= width) || (y < 0) || (y >= height)) return;  
	buffer[y*width + x] = c;
}
void PartialBuffer::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t c)
{
	if((x >= 0) && (x < width)) { 
    if(y < 0) {
		h +=y;
		y = 0;
    }
    if((y + h) > height) { 
        h = (height - y);
    }
    if(h > 0) { 
		while (h-- > 0) {
			buffer[(h+y)*width + x] = c;
		}
	}
	}
}

void PartialBuffer::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c)
{
    if((y >= 0) && (y < height)) { 
		if(x < 0) {  
			w += x;
			x  = 0;
		}
		if((x + w) > width) { 
			w = (width - x);
		}
		if(w > 0) {
			uint16_t buff_loc = y*width + x;
			while (w-- > 0) {
				buffer[buff_loc + w] = c;
			}
		} 
	}
} 
void PartialBuffer::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c){
    if(w && h) {                            
        if(w < 0) {                          
            x +=  w + 1;                  
            w  = -w;                       
        }
        if(x < width) {                      
            if(h < 0) {                     
                y +=  h + 1;               
                h  = -h;                    
            }
            if(y < height) {             
                int16_t x2 = x + w - 1;
                if(x2 >= 0) {              
                    int16_t y2 = y + h - 1;
                    if(y2 >= 0) {           
                        if(x  <  0) { x = 0; w = x2 + 1;}
                        if(y  <  0) { y = 0; h = y2 + 1;}
                        if(x2 >= width) { w = width  - x;} 
                        if(y2 >= height) { h = height - y;}
						while(h-- >0) {
							for(int16_t i=0; i<w; i++) {
								buffer[(h+y)*width + x + i] = c;
							}
						}
                    }
                }
            }
        }
    }	
}
void PartialBuffer::fillScreen(uint16_t c) {
	uint8_t c1 = c & 0xFF;  
	uint8_t c2 = (uint8_t)(c>>8);
	uint32_t buff_len = width * height;
	if(c1 == c2){
		memset(buffer, c, buff_len * 2); //Special case, speed up
	}else{ 
		while(buff_len-- >0){
			buffer[buff_len] = c;
		}
	}
} 
uint16_t *PartialBuffer::bufferOut() {
	return buffer;
}
uint16_t PartialBuffer::pixelOut(int16_t x, int16_t y) {
	//uint8_t c1 = buffer[y*width*2 + x*2];
	//uint8_t c2 = buffer[y*width*2 + x*2 + 1];
	//uint16_t c = ((uint16_t)c2 << 8) | c1;
	return buffer[y*width + x];
}

