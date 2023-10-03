/*
 *    UNOR4WMatrixGFX.h - A library for controling the
 *    led matrix on the Arduino UNO R4 WIFI boards.
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
*/
#include "UNOR4WMatrixGFX.h"

//#define DEBUG_PRINT

#ifdef DEBUG_PRINT
#define DBGPrintf printf
#else
inline void DBGPrintf(...) {}
#endif
#define NUM_LEDS    96

static const int pin_zero_index = 28;

const uint8_t UNOR4WMatrixGFX::pins[][2] = {
  { 7, 3 }, { 3, 7 }, { 7, 4 }, { 4, 7 }, { 3, 4 }, { 4, 3 }, { 7, 8 }, { 8, 7 }, { 3, 8 }, { 8, 3 }, { 4, 8 }, { 8, 4 },
  { 7, 0 }, { 0, 7 }, { 3, 0 }, { 0, 3 }, { 4, 0 }, { 0, 4 }, { 8, 0 }, { 0, 8 }, { 7, 6 }, { 6, 7 }, { 3, 6 }, { 6, 3 },
  { 4, 6 }, { 6, 4 }, { 8, 6 }, { 6, 8 }, { 0, 6 }, { 6, 0 }, { 7, 5 }, { 5, 7 }, { 3, 5 }, { 5, 3 }, { 4, 5 }, { 5, 4 },
  { 8, 5 }, { 5, 8 }, { 0, 5 }, { 5, 0 }, { 6, 5 }, { 5, 6 }, { 7, 1 }, { 1, 7 }, { 3, 1 }, { 1, 3 }, { 4, 1 }, { 1, 4 },
  { 8, 1 }, { 1, 8 }, { 0, 1 }, { 1, 0 }, { 6, 1 }, { 1, 6 }, { 5, 1 }, { 1, 5 }, { 7, 2 }, { 2, 7 }, { 3, 2 }, { 2, 3 },
  { 4, 2 }, { 2, 4 }, { 8, 2 }, { 2, 8 }, { 0, 2 }, { 2, 0 }, { 6, 2 }, { 2, 6 }, { 5, 2 }, { 2, 5 }, { 1, 2 }, { 2, 1 },
  { 7, 10 }, { 10, 7 }, { 3, 10 }, { 10, 3 }, { 4, 10 }, { 10, 4 }, { 8, 10 }, { 10, 8 }, { 0, 10 }, { 10, 0 }, { 6, 10 }, { 10, 6 },
  { 5, 10 }, { 10, 5 }, { 1, 10 }, { 10, 1 }, { 2, 10 }, { 10, 2 }, { 7, 9 }, { 9, 7 }, { 3, 9 }, { 9, 3 }, { 4, 9 }, { 9, 4 }
};

uint32_t volatile * const UNOR4WMatrixGFX::matrix_pin_pmnpfs[] = {
     &R_PFS->PORT[(g_pin_cfg[0 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[0 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[1 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[1 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[2 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[2 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[3 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[3 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[4 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[4 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[5 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[5 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[6 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[6 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[7 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[7 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[8 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[8 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[9 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[9 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[10 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[10 + pin_zero_index].pin) & 0xFF].PmnPFS,
     &R_PFS->PORT[(g_pin_cfg[0 + pin_zero_index].pin) >> 8].PIN[(g_pin_cfg[0 + pin_zero_index].pin) & 0xFF].PmnPFS // copy of 0
};


const int8_t UNOR4WMatrixGFX::matrix_irq_pins[11][10] = {
{50/*01*/, 64/*02*/, 15/*03*/, 17/*04*/, 38/*05*/, 28/*06*/, 13/*07*/, 19/*08*/, 80/*10*/, -9},      // high 0
{51/*00*/, 70/*02*/, 45/*03*/, 47/*04*/, 55/*05*/, 53/*06*/, 43/*07*/, 49/*08*/, 86/*10*/, -9},      // High 1
{65/*00*/, 71/*01*/, 59/*03*/, 61/*04*/, 69/*05*/, 67/*06*/, 57/*07*/, 63/*08*/, 88/*10*/, -9},      // High 2
{14/*00*/, 44/*01*/, 58/*02*/, 4/*04*/, 32/*05*/ , 22/*06*/, 1/*07*/, 8/*08*/, 92/*09*/, 74/*10*/},  // High 3
{16/*00*/, 46/*01*/, 60/*02*/, 5/*03*/, 34/*05*/ , 24/*06*/, 3/*07*/, 10/*08*/, 94/*09*/, 76/*10*/}, // High 4
{39/*00*/, 54/*01*/, 68/*02*/, 33/*03*/, 35/*04*/, 41/*06*/, 31/*07*/, 37/*08*/ , 84/*10*/, -9},     // High 5
{29/*00*/, 52/*01*/, 66/*02*/, 23/*03*/, 25/*04*/, 40/*05*/, 21/*07*/, 27/*08*/, 82/*10*/, -9},      // High 6
{12/*00*/, 42/*01*/, 56/*02*/, 0/*03*/, 2/*04*/,   30/*05*/, 20/*06*/, 6/*08*/, 90/*09*/, 72/*10*/}, // High 7
{18/*00*/, 48/*01*/, 62/*02*/, 9/*03*/, 11/*04*/,  36/*05*/ , 26/*06*/, 7/*07*/, 78/*10*/, -9},      // High 8
{93/*03*/, 95/*04*/, 91/*07*/, /*-0*/-11,     -1,        -2,       -5,        -6,      -8, -10,},    // High 9
{81/*00*/, 87/*01*/, 89/*02*/, 75/*03*/, 77/*04*/, 85/*05*/, 83/*06*/, 73/*07*/, 79/*08*/, -9},      // High 10

};

#define LED_MATRIX_PORT0_MASK       ((1 << 3) | (1 << 4) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 15))
#define LED_MATRIX_PORT2_MASK       ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 12) | (1 << 13))

//=============================================================================
// Static members - should probably be most/all of them.
//=============================================================================
FspTimer UNOR4WMatrixGFX::s_ledTimer;
uint8_t __attribute__((aligned)) UNOR4WMatrixGFX::s_framebuffer[(NUM_LEDS * BITS_PER_PIXEL) / 8];
uint8_t UNOR4WMatrixGFX::s_high_pin_index = 0xff;
uint8_t UNOR4WMatrixGFX::s_turn_off_pulse_color = 0;
uint32_t UNOR4WMatrixGFX::s_rawPeriods[4] = {0, 0, 0, 0};
volatile uint32_t UNOR4WMatrixGFX::s_rawPeriodOn = 0;
volatile uint32_t UNOR4WMatrixGFX::s_rawPeriodOff = 0;
volatile uint32_t UNOR4WMatrixGFX::s_frame_index = 0;
R_GPT0_Type *UNOR4WMatrixGFX::s_pgpt0 = nullptr;


UNOR4WMatrixGFX::UNOR4WMatrixGFX()
  : Adafruit_GFX(MATRIX_WIDTH, MATRIX_HEIGHT) {
  fillScreen(MATRIX_BLACK);
}

// destructor
UNOR4WMatrixGFX::~UNOR4WMatrixGFX() {
}

//=============================================================================
// Begin
//=============================================================================
bool UNOR4WMatrixGFX::begin(uint32_t frames_per_second, Stream *debugStream ) {
  uint8_t type;
  uint8_t ch = FspTimer::get_available_timer(type);

  _debugStream = debugStream;
#ifdef MATRIX_INT_PER_PIXEL
  uint32_t frequency = frames_per_second * NUM_LEDS;
#else 
  uint32_t frequency = frames_per_second * 11;
#endif

  R_PORT0->PCNTR1 &= ~((uint32_t) LED_MATRIX_PORT0_MASK);
  R_PORT2->PCNTR1 &= ~((uint32_t) LED_MATRIX_PORT2_MASK);
  
  _pulseWidth =  1000000.0 / frequency;
  if (_debugStream) {
    _debugStream->print("Freq: ");
    _debugStream->print(frequency, DEC);
    _debugStream->print(" Pulse Width:");
    _debugStream->println(_pulseWidth, DEC);
    _debugStream->print("ch:");
    _debugStream->print(ch, DEC);
    _debugStream->print(" type:");
    _debugStream->println(type, DEC);
  }
  
  _new_period_on_percent = 0.0;
  s_ledTimer.begin(TIMER_MODE_PERIODIC, type, ch, _pulseWidth, 50.0, led_timer_callback, this);

  // lets get the pointer to the GPT object.
  s_pgpt0 = (R_GPT0_Type *)((uint32_t)R_GPT0 + ((uint32_t)R_GPT1 - (uint32_t)R_GPT0) * ch);
  // turn off GTPR Buffer 
  s_pgpt0->GTBER_b.PR = 0;
  s_pgpt0->GTBER_b.BD1 = 1;

  s_ledTimer.setup_overflow_irq();
  s_ledTimer.open();
  s_ledTimer.start();

  // Now lets see what the period;
  s_rawPeriods[0] = s_ledTimer.get_period_raw();
  if (_debugStream) {
    _debugStream->print("Period:");
    _debugStream->println(s_rawPeriods[0], DEC);
  }
  
  s_rawPeriodOn = s_rawPeriods[0];
  s_rawPeriods[1] = s_rawPeriods[0] / 8;
  s_rawPeriods[2] = s_rawPeriods[0] / 4;
  s_rawPeriods[3] = s_rawPeriods[0];  // duplicate of 0
  s_rawPeriodOff = 0;
  return true;
}

void UNOR4WMatrixGFX::display() {
  memcpy(s_framebuffer, _frame_buffer, sizeof(_frame_buffer));
}


float UNOR4WMatrixGFX::colorPeriodPercent(uint8_t index) {
  if ((index >= 1) && (index <= 3)) return float(s_rawPeriods[index]) / float(s_rawPeriods[0]);
  return 0.0f;
}

void UNOR4WMatrixGFX::colorPeriodPercent(uint8_t index, float percent) {
  if ((index >= 1) && (index <= 3)) {
    s_rawPeriods[index] = float(s_rawPeriods[0]) * percent;
  }
}



// virtual overrides - start simple
static inline void swap(int16_t &x, int16_t &y) {
  int16_t t = x;
  x = y;
  y = t;
}

inline void UNOR4WMatrixGFX::pixel(uint8_t pixel_index, uint16_t color) {
  // 2 bits per pixel
  uint8_t byte_index = pixel_index >> 2;
  uint8_t shift = (pixel_index & 0x3) * 2;
  _frame_buffer[byte_index] =  ((_frame_buffer[byte_index]) & ~(COLOR_MASK << shift)) 
      | (color & COLOR_MASK) << shift; 
}

uint16_t UNOR4WMatrixGFX::pixelDisp(uint8_t pixel_index) {
  // 2 bits per pixel
  uint8_t byte_index = pixel_index >> 2;
  uint8_t shift = (pixel_index & 0x3) * 2;
  return (s_framebuffer[byte_index] >> shift) & COLOR_MASK;
}


uint16_t UNOR4WMatrixGFX::getPixel(int16_t x, int16_t y) {
  uint16_t pixel_index = y * MATRIX_WIDTH + x;
  uint8_t byte_index = pixel_index >> 2;
  uint8_t shift = (pixel_index & 0x3) * 2;
  return (_frame_buffer[byte_index] >> shift) & COLOR_MASK;
}

void UNOR4WMatrixGFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
  switch (getRotation()) {
    case 1:
      swap(x, y);
      x = MATRIX_WIDTH - x - 1;
      break;
    case 2:
      x = MATRIX_WIDTH - x - 1;
      y = MATRIX_HEIGHT - y - 1;
      break;
    case 3:
      swap(x, y);
      y = MATRIX_HEIGHT - y - 1;
      break;
  }
  if ((x < 0 ) || (x >= MATRIX_WIDTH)) return;
  if ((y < 0 ) || (y >= MATRIX_HEIGHT)) return;
  
  pixel(y * MATRIX_WIDTH + x, color);
}

void UNOR4WMatrixGFX::fillScreen(uint16_t color) {
  if (color == MATRIX_WHITE) {
    memset(_frame_buffer, 0xff, sizeof(_frame_buffer));
  } else {
    memset(_frame_buffer, 0x00, sizeof(_frame_buffer));
  }
}

void UNOR4WMatrixGFX::clearDisplay() {
  fillScreen(MATRIX_BLACK);
}

void UNOR4WMatrixGFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  DBGPrintf("\t\t\tFHline(%d, %d, %d, %x ->", x, y, w, textcolor);
  bool swapped = false;
  switch (getRotation()) {
    case 1:
      swap(x, y);
      swapped = true;
      x = MATRIX_WIDTH - x - 1;
      break;
    case 2:
      x = MATRIX_WIDTH - (x+w);
      y = MATRIX_HEIGHT - y - 1;
      break;
    case 3:
      swap(x, y);
      swapped = true;
      y = MATRIX_HEIGHT - (y + w);
      break;
  }

  if (swapped) vline(x, y, w, color);
  else hline(x, y, w, color);
}

void UNOR4WMatrixGFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  DBGPrintf("\t\t\tFVline(%d, %d, %d, %x ->", x, y, h, textcolor);
  bool swapped = false;
  switch (getRotation()) {
    case 1:
      swap(x, y);
      swapped = true;
      x = MATRIX_WIDTH - (x + h);
      break;
    case 2:
      x = MATRIX_WIDTH - x - 1;
      y = MATRIX_HEIGHT - (y+h);
      break;
    case 3:
      swap(x, y);
      swapped = true;
      y = MATRIX_HEIGHT - y - 1;
      break;
  }

  if (swapped) hline(x, y, h, color);
  else vline(x, y, h, color);

}


void UNOR4WMatrixGFX::hline(int16_t x, int16_t y, int16_t w, uint16_t color) {
  DBGPrintf("hline(%d, %d, %d, %x\n", x, y, w, textcolor);

  if ((y < 0 ) || (y >= MATRIX_HEIGHT)) return;
  int16_t x_end = x + w;
  if (x < 0) x = 0;
  if (x_end > MATRIX_WIDTH) x_end = MATRIX_WIDTH;

  uint8_t pixel_index = y * MATRIX_WIDTH + x;
  while (x < x_end) {
    pixel(pixel_index, color);
    x++;
    pixel_index++;
  }
}

void UNOR4WMatrixGFX::vline(int16_t x, int16_t y, int16_t h, uint16_t color) {
  DBGPrintf("vline(%d, %d, %d, %x\n", x, y, h, textcolor);
  if ((x < 0 ) || (x >= MATRIX_WIDTH)) return;
  int16_t y_end = y + h;
  if (y < 0) y = 0;
  if (y_end > MATRIX_HEIGHT) y_end = MATRIX_HEIGHT;

  uint8_t pixel_index = y * MATRIX_WIDTH + x;
  while (y < y_end) {
    pixel(pixel_index, color);
    y++;
    pixel_index += MATRIX_WIDTH;
  }
}

void UNOR4WMatrixGFX::updateClockPeriod(uint32_t period) {
  if (s_pgpt0) s_pgpt0->GTPR = period;
  else s_ledTimer.set_period(period);
}


//=================================================================================
// Test to support ILI ilifont code
//=================================================================================

// See if we can overwrite the print write method
static uint32_t fetchbit(const uint8_t *p, uint32_t index) {
  if (p[index >> 3] & (1 << (7 - (index & 7))))
    return 1;
  return 0;
}

static uint32_t fetchbits_unsigned(const uint8_t *p, uint32_t index,
                                   uint32_t required) {
  uint32_t val = 0;
  do {
    uint8_t b = p[index >> 3];
    uint32_t avail = 8 - (index & 7);
    if (avail <= required) {
      val <<= avail;
      val |= b & ((1 << avail) - 1);
      index += avail;
      required -= avail;
    } else {
      b >>= avail - required;
      val <<= required;
      val |= b & ((1 << required) - 1);
      break;
    }
  } while (required);
  return val;
}

static uint32_t fetchbits_signed(const uint8_t *p, uint32_t index,
                                 uint32_t required) {
  uint32_t val = fetchbits_unsigned(p, index, required);
  if (val & (1 << (required - 1))) {
    return (int32_t)val - (1 << required);
  }
  return (int32_t)val;
}


size_t UNOR4WMatrixGFX::write(uint8_t c) {

  if (!ilifont) return Adafruit_GFX::write(c);
  return drawILIFontChar(this, ilifont, wrap, textcolor, c);  
}

//-----------------------------------------------------------------------------
// Standalone version.
static void drawILIFontBits(Adafruit_GFX *gfx, uint16_t textcolor, uint32_t bits, uint32_t numbits, uint32_t x, uint32_t y, uint32_t repeat)
{
  if (bits == 0) return;
  uint32_t w;
  bits <<= (32-numbits); // left align bits 
  do {
    w = __builtin_clz(bits); // skip over zeros
    if (w > numbits) w = numbits;
    numbits -= w;
    x += w;
    bits <<= w;
    bits = ~bits; // invert to count 1s as 0s
    w = __builtin_clz(bits);
    if (w > numbits) w = numbits; 
    numbits -= w;
    bits <<= w;
    bits = ~bits; // invert back to original polarity
    if (w > 0) {
      DBGPrintf("\t\tfillRect(%u, %u, %u, %u, %x\n", x, y, w, repeat, textcolor);
      gfx->fillRect(x, y, w, repeat, textcolor);
      x += w;
    }
  } while (numbits > 0);
}




size_t drawILIFontChar(Adafruit_GFX *gfx, const ILI9341_t3_font_t *ilifont, bool wrap, uint16_t textcolor, char c)
{
  if (!ilifont) return gfx->write(c);

    uint32_t bitoffset;
  const uint8_t *data;

  DBGPrintf("drawFontChar %d\n", c);

  if (c >= ilifont->index1_first && c <= ilifont->index1_last) {
    bitoffset = c - ilifont->index1_first;
    bitoffset *= ilifont->bits_index;
  } else if (c >= ilifont->index2_first && c <= ilifont->index2_last) {
    bitoffset = c - ilifont->index2_first + ilifont->index1_last - ilifont->index1_first + 1;
    bitoffset *= ilifont->bits_index;
  } else {
    return 0;
  }
  DBGPrintf("  index =  %d\n", fetchbits_unsigned(ilifont->index, bitoffset, ilifont->bits_index));
  data = ilifont->data + fetchbits_unsigned(ilifont->index, bitoffset, ilifont->bits_index);

  uint32_t encoding = fetchbits_unsigned(data, 0, 3);
  if (encoding != 0) return 0;
  uint32_t width = fetchbits_unsigned(data, 3, ilifont->bits_width);
  bitoffset = ilifont->bits_width + 3;
  uint32_t height = fetchbits_unsigned(data, bitoffset, ilifont->bits_height);
  bitoffset += ilifont->bits_height;
  DBGPrintf("  size =   %d,%d\n", width, height);

  int32_t xoffset = fetchbits_signed(data, bitoffset, ilifont->bits_xoffset);
  bitoffset += ilifont->bits_xoffset;
  int32_t yoffset = fetchbits_signed(data, bitoffset, ilifont->bits_yoffset);
  bitoffset += ilifont->bits_yoffset;
  DBGPrintf("  offset = %d,%d\n", xoffset, yoffset);

  uint32_t delta = fetchbits_unsigned(data, bitoffset, ilifont->bits_delta);
  bitoffset += ilifont->bits_delta;
  DBGPrintf("  delta =  %d\n", delta);

  int16_t cursor_x = gfx->getCursorX();
  int16_t cursor_y = gfx->getCursorY();
  DBGPrintf("  cursor = %d,%d\n", cursor_x, cursor_y);

  // horizontally, we draw every pixel, or none at all
  if (cursor_x < 0) cursor_x = 0;

  int32_t origin_x = cursor_x + xoffset;
  if (origin_x < 0) {
    cursor_x -= xoffset;
    origin_x = 0;
  }
  if (origin_x + (int)width > gfx->width()) {
    // I am going to allow partial characters to be output
    if (wrap) {
      origin_x = 0;
      if (xoffset >= 0) {
        cursor_x = 0;
      } else {
        cursor_x = -xoffset;
      }
      cursor_y += ilifont->line_space;
    }
  }
  //if (cursor_y >= _height) return 1;
  cursor_x += delta;

  // vertically, the top and/or bottom can be clipped
  int32_t origin_y = cursor_y + ilifont->cap_height - height - yoffset;
  DBGPrintf("  cy:%d cap:%d height:%d yof:%d\n", cursor_y, ilifont->cap_height, height, yoffset);
  DBGPrintf("  origin = %d,%d\n", origin_x, origin_y);

  // TODO: compute top skip and number of lines
  int32_t linecount = height;
  //uint32_t loopcount = 0;
  uint32_t y = origin_y;
  while (linecount) {
    DBGPrintf("    linecount = %d\n", linecount);
    uint32_t b = fetchbit(data, bitoffset++);
    if (b == 0) {
      DBGPrintf("    single line\n");
      uint32_t x = 0;
      do {
        uint32_t xsize = width - x;
        if (xsize > 32) xsize = 32;
        uint32_t bits = fetchbits_unsigned(data, bitoffset, xsize);
        drawILIFontBits(gfx, textcolor, bits, xsize, origin_x + x, y, 1);
        bitoffset += xsize;
        x += xsize;
      } while (x < width);
      y++;
      linecount--;
    } else {
      uint32_t n = fetchbits_unsigned(data, bitoffset, 3) + 2;
      bitoffset += 3;
      uint32_t x = 0;
      do {
        uint32_t xsize = width - x;
        if (xsize > 32) xsize = 32;
        DBGPrintf("    multi line %d\n", n);
        uint32_t bits = fetchbits_unsigned(data, bitoffset, xsize);
        drawILIFontBits(gfx, textcolor, bits, xsize, origin_x + x, y, n);
        bitoffset += xsize;
        x += xsize;
      } while (x < width);
      y += n;
      linecount -= n;
    }
    //if (++loopcount > 100) {
      //Serial.println("     abort draw loop");
      //break;
    //}
  }
  // update the GFX cursor.
  gfx->setCursor(cursor_x, cursor_y);
  return 1;

}



//=================================================================================
// Timer ISR Callback - one pixel and a timer version. 
//=================================================================================
#ifdef MATRIX_INT_PER_PIXEL
void UNOR4WMatrixGFX::led_timer_callback(timer_callback_args_t *arg) {
    if (arg == nullptr || arg->p_context == nullptr) return; // ???

    // turn all of the pins to input.
    #ifdef R4MATRIX_DEBUG_PINS
    digitalWriteFast(3, LOW); 
    #endif
    R_PORT0->PCNTR1 &= ~((uint32_t) LED_MATRIX_PORT0_MASK);
    R_PORT2->PCNTR1 &= ~((uint32_t) LED_MATRIX_PORT2_MASK);
    static volatile int i_isr = 0;
    // See if 
    if (s_rawPeriodOff) {
        // only pupose was to turn off the leds
        updateClockPeriod(s_rawPeriodOff); // how long it will off
        s_rawPeriodOff = 0;
        return;
    }        
    uint8_t pixel_color = pixelDisp(i_isr);
    uint32_t lastRawPeriodOn = s_rawPeriodOn; 

    if (pixel_color != 0) {
      #ifdef R4MATRIX_DEBUG_PINS
      digitalWriteFast(3, HIGH); 
      #endif
      *matrix_pin_pmnpfs[pins[i_isr][0]] = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_HIGH;
      *matrix_pin_pmnpfs[pins[i_isr][1]] = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW;
      switch (pixel_color) {
        default: s_rawPeriodOn = s_rawPeriods[0]; break;
        case 1: s_rawPeriodOn = s_rawPeriods[1]; break;
        case 2: s_rawPeriodOn = s_rawPeriods[2]; break;  
      }
    } else {
      s_rawPeriodOn = s_rawPeriods[0];
    }

    if ((s_rawPeriodOn != s_rawPeriods[0]) || (lastRawPeriodOn != s_rawPeriods[0])) {
       updateClockPeriod(s_rawPeriodOn); // how long it will off
    }
    s_rawPeriodOff = s_rawPeriods[0] - s_rawPeriodOn;
    i_isr = (i_isr + 1) % NUM_LEDS;

}
#else
//=================================================================================
// Timer ISR Callback - Process all leds associated with HIGH pin in one pass
//=================================================================================
void UNOR4WMatrixGFX::led_timer_callback(timer_callback_args_t *arg) {
    if (arg == nullptr || arg->p_context == nullptr) return; // ???

    // turn all of the pins to input.
    #ifdef R4MATRIX_DEBUG_PINS
    digitalWriteFast(3, LOW); 
    #endif


    //ArduinoLEDMatrixGFX* _m   = (ArduinoLEDMatrixGFX*)arg->p_context;

    //-------------------------------------------------------------
    // This gets a little more complex 
    // as we may be turning off leds through a set of interrupts.
    //-------------------------------------------------------------
    //R_PORT0->PCNTR1 &= ~((uint32_t) LED_MATRIX_PORT0_MASK);
    //R_PORT2->PCNTR1 &= ~((uint32_t) LED_MATRIX_PORT2_MASK);
    //Serial.print(s_high_pin_index, DEC); Serial.print(" ");
    //Serial.print(s_turn_off_pulse_color, DEC);
    //Serial.println();

    if (s_turn_off_pulse_color && (s_high_pin_index < 11)) {
      uint8_t next_off_color = 0x4;
      for (uint8_t i = 0; i < 10; i++) {
        int8_t led = matrix_irq_pins[s_high_pin_index][i];
        if (led < 0) break;
        uint8_t pixel_color = pixelDisp(led);
        if (pixel_color == s_turn_off_pulse_color) {
          // turn the pin back to input.
          *matrix_pin_pmnpfs[pins[led][1]] = IOPORT_CFG_PORT_DIRECTION_INPUT;
        } else if ((pixel_color > s_turn_off_pulse_color) && (pixel_color < next_off_color)) {
          next_off_color = pixel_color;
        }
      }
      if (next_off_color == 0x4) {
        // We can turn off the high pin now...
        *matrix_pin_pmnpfs[s_high_pin_index] = IOPORT_CFG_PORT_DIRECTION_INPUT;
      }
      if (s_turn_off_pulse_color < 0x3) {
        // need to compute the next timer setting.
        if ((s_turn_off_pulse_color == 1) && (next_off_color == 2)) {
          updateClockPeriod(s_rawPeriods[2] - s_rawPeriods[1]);
        } else {
          updateClockPeriod(s_rawPeriods[0] - s_rawPeriods[s_turn_off_pulse_color]);
        }
        s_turn_off_pulse_color = next_off_color;
        return;
      }

    }

    //-------------------------------------------------------------
    // Now lets get to the next HIGH pin and see if we have any
    // LEDS to turn on.
    //-------------------------------------------------------------
    s_high_pin_index++;
    if (s_high_pin_index >= 11) {
      s_high_pin_index = 0;

      s_frame_index++; 
    }  

    s_turn_off_pulse_color = 4;
    for (uint8_t i = 0; i < 10; i++) {
      int8_t led = matrix_irq_pins[s_high_pin_index][i];
      if (led < 0) {
        // If < 0 then we have pins not used for this row, make sure they are low
        *matrix_pin_pmnpfs[-led] = IOPORT_CFG_PORT_DIRECTION_INPUT;
      } else {
        uint8_t pixel_color = pixelDisp(led);
        if (pixel_color) {
          if (s_turn_off_pulse_color == 4) {
            *matrix_pin_pmnpfs[s_high_pin_index] = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_HIGH;
           #ifdef R4MATRIX_DEBUG_PINS
           digitalWriteFast(3, HIGH); 
           #endif
          }
          *matrix_pin_pmnpfs[pins[led][1]] = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW;
          if (pixel_color < s_turn_off_pulse_color) s_turn_off_pulse_color = pixel_color;
        } else {
          *matrix_pin_pmnpfs[pins[led][1]] = IOPORT_CFG_PORT_DIRECTION_INPUT;

        }
      }
    }

    // Update the clock.
    if (s_turn_off_pulse_color == 4) {
      s_turn_off_pulse_color = 0;  // don't need to do anything as we did not turn anything on
    }
    updateClockPeriod(s_rawPeriods[s_turn_off_pulse_color]);
}
#endif


