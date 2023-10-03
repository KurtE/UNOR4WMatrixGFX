Overview and Warning: 
=====

Work in Progress

This Arduino library, is a display like driver based on the Adafruit_GFX library
to drive the Charlieplex display on the Arduino UNO R4 WiFi boards.

This is an alternative to the library Arduino_LED_Matrix that ships with the UNO R4 board instals.
This library does not support the methods that are part of the Arduino_LED_Matrix

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

There is additional information about the led matrix as well as the official
library for it up at https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix

There is also additional information on the cheat sheet: https://docs.arduino.cc/tutorials/uno-r4-wifi/cheat-sheet#led-matrix

Some Implementation and Usage Details
=======
Frames
-----
This library does not use the Frames as defined in the other library.  Instead you are free to use whatever
GFX functions, fonts, bitmaps, canvas and the like

Fonts
-----
This library supports all of the GFX built in font as well as other GFX fonts.  
However most all of these fonts are taller than the matrix.  So in addition
to these fonts, I added in support for the ILI9341_t3 fonts that we use in
a lot of the display drivers for the Teensy boards (PJRC).

You can find a lot of these fonts up in the github project:
https://github.com/mjs513/ILI9341_fonts

The font_test example will not complile without the fonts library installed. 

Timer and Interrupts
--------
This library uses the FSP timers, which are not officially documented but a several
of the other libraries including Arduino_LED_Matrixthe use it.  There is a good writeup
about it up at: https://www.pschatzmann.ch/home/2023/07/01/under-the-hood-arduino-uno-r4-timers/

The Arduino_LED_Matrix library uses the timer causes an interrupt for each led per frame, so if
you are setup for 10 frames per second it interrupt 8*12*10 or 960 interrupt per second. 

In this implementation, I only drive one pin HIGH per interrupt, and will check all of the LEDs
that are logically set that this pin drives and set the corresponding IO pin LOW, else will
leave the others in the READ state. So in simple cases only need 12 interrupt per frame.
But I added some additional capabilities, which may increase the number of interrupts.

Logical Color/Intensity
---
Like other sub-classes of the Adafruit_GFX library, the graphic primitives allow you to specify
the color to draw with.  So I defined a few colors
````
#define MATRIX_BLACK  0   ///< Draw 'off' pixels
#define MATRIX_DARK   0x1
#define MATRIX_LIGHT  0x2
#define MATRIX_WHITE  0x3   ///< Draw 'on' pixels
```

The code uses the logical color of the pixel, to decide how long that LED will be driven high per frame. It is not
perfect, but does allow you a couple of different intensities.

Example Sketch
-----

```
#include <UNOR4WMatrixGFX.h>
UNOR4WMatrixGFX display;
void setup() {
  // put your setup code here, to run once:
  display.begin();
  display.clearDisplay();

  uint8_t colors[] = { MATRIX_WHITE, MATRIX_DARK, MATRIX_LIGHT, MATRIX_BLACK };
  for (int16_t i = 0; i < 4; i++) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, colors[i]);
    display.display();  // Update screen with each newly-drawn rectangle
    delay(250);
  }
}

uint8_t loop_count = 0;
void loop() {
  loop_count++;
  delay(1000);
  display.fillRect(3, 3, display.width() - 6, display.height() - 6, (loop_count & 1)? MATRIX_WHITE : MATRIX_BLACK);
  display.display();  // Update screen with each newly-drawn rectangle
}
```


No Promises
====
I am doing this for the fun of it.  There are no guarantees or warranties, that this library
works or is good for anything.  But I hope it is.

Kurt


