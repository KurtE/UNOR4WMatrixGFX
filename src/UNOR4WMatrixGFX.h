/*
 *    UNOR4WMatrixGFX.h - A library for controling the
 *    led matrix on the Arduino UNO R4 WIFI boards.
 *
 *    Part of this code is based on the Arduino_LED_Matrix.h code that is part of the
 *    Arduino UNO R4 code base
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

#ifndef _UNOR4WiFi_Matrix_GFX_h_
#define _UNOR4WiFi_Matrix_GFX_h_
#include "FspTimer.h"

// Uncomment if you want to enable the digital pins for debug
//#define R4MATRIX_DEBUG_PINS
#ifdef R4MATRIX_DEBUG_PINS
#include "UNOR4_digitalWriteFast.h"
#endif

#include <Adafruit_GFX.h>
#include "ILI9341_fonts.h"
#define MATRIX_BLACK  0   ///< Draw 'off' pixels
#define MATRIX_DARK   0x1
#define MATRIX_LIGHT  0x2
#define MATRIX_WHITE  0x3   ///< Draw 'on' pixels

#define MATRIX_WIDTH 12
#define MATRIX_HEIGHT 8

#ifndef NO_ADAFRUIT_COLOR_COMPATIBILITY
#define BLACK MATRIX_BLACK     ///< Draw 'off' pixels
#define WHITE MATRIX_WHITE     ///< Draw 'on' pixels
#endif

//#define MATRIX_INT_PER_PIXEL

// Define a stand along function that can output a singlt ILIFont character
size_t drawILIFontChar(Adafruit_GFX *gfx, const ILI9341_t3_font_t *ilifont, bool wrap, uint16_t textcolor, char c);


class UNOR4WMatrixGFX : public Adafruit_GFX {
  public:
    // constructor
    UNOR4WMatrixGFX(); 

    // destructor
    ~UNOR4WMatrixGFX(); 

    #ifdef MATRIX_INT_PER_PIXEL
    // begin start up the underlying matrix object
    bool begin(uint32_t frames_per_second = 1, Stream *debugStream = nullptr);

    #else
    // begin start up the underlying matrix object
    bool begin(uint32_t frames_per_second = 10, Stream *debugStream = nullptr);
    #endif

    // Clears the frame buffer;
    void clearDisplay();

    // Update the screen from the current frame buffer
    void display();

    // Get the current frame index.
    uint32_t frameIndex() {return s_frame_index;}

    // overrides - draw pixel to frame buffer
    virtual  void drawPixel(int16_t x, int16_t y, uint16_t color);

    // quick overwrite of the GFX library fillScreen
    virtual void fillScreen(uint16_t color);


    // Override of the GFX method
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

    // Override of the GFX method
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);


    // The actual code to draw the horizontal line after the 
    // rotation of the screen has been taken into account.
    void hline(int16_t x, int16_t y, int16_t w, uint16_t color);

    // The actual code to draw the Vertical line
    void vline(int16_t x, int16_t y, int16_t h, uint16_t color);



    // Added ability to use ILI9341 fonts like those in ILI9341_t3 library
    // Note: You need to call this with nullptr to allow the code to use
    // any of the standard GFX fonts.
    void setILIFont(const ILI9341_t3_font_t *f) {
      ilifont = f;
    }

    // Overwrite the write print write method to allow us to intercept
    // display.print(...) lines and handle ILI font.
    virtual size_t write(uint8_t);

    // retrieves the current pixel from the frame buffer
    uint16_t getPixel(int16_t x, int16_t y);

    static inline void updateClockPeriod(uint32_t period);


    // Lets setup ways to update the pulse widths for different color setting
    // valid index 1-3. percent <= 1.0
    float colorPeriodPercent(uint8_t index);
    void colorPeriodPercent(uint8_t index, float percent);

    // Some of this should be protectdd or private:

    inline void pixel(uint8_t pixel_index, uint16_t color);
    static uint16_t pixelDisp(uint8_t pixel_index);

    enum {NUM_LEDS=96, BITS_PER_PIXEL=2, COLOR_MASK = 0x3};

    uint32_t _pulseWidth;
    float _new_period_on_percent;

    // Interrupt callback
    static void led_timer_callback(timer_callback_args_t *arg);
    uint8_t __attribute__((aligned)) _frame_buffer[(NUM_LEDS * BITS_PER_PIXEL) / 8];

    static uint8_t __attribute__((aligned)) s_framebuffer[(NUM_LEDS * BITS_PER_PIXEL) / 8];
    static uint8_t s_high_pin_index;
    static uint8_t s_turn_off_pulse_color;

    static FspTimer s_ledTimer;
    static uint32_t s_rawPeriods[4];
    static volatile uint32_t s_rawPeriodOn;
    static volatile uint32_t s_rawPeriodOff;
    static volatile uint32_t s_frame_index;
    static R_GPT0_Type *s_pgpt0;

    // Font stuff
    const ILI9341_t3_font_t *ilifont = nullptr;

    static uint32_t volatile * const matrix_pin_pmnpfs[];
    static const uint8_t pins[96][2];
    static const int8_t matrix_irq_pins[11][10];

    Stream *_debugStream = nullptr;

};

#endif
