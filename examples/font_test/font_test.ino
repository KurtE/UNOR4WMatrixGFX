//=============================================================================
// This example sketch scrolls through drawing the all of the characters of
// a font. Currently it is only doing the default GFX font as well as a few
// ILI9341 fonts.
// Most of these fonts are part of another font library you can download from
// github: https://github.com/mjs513/ILI9341_fonts
// If you have this library uncomment the define: USE_ILI_FONT_LIBRARY to
// use the additional fonts
//
// Note: This sketch waits for you to type something in between each font.
// If the first character you type in is a $ it will disable this pause.  
// entering $ again will enable the wait between fonts
//=============================================================================
//#define USE_ILI_FONT_LIBRARY

#include <UNOR4WMatrixGFX.h>
#include <UNOR4W_matrix_font_Arial89.h>

#ifdef USE_ILI_FONT_LIBRARY
#include "font_ArialBold.h"
#include "font_ComicSansMS.h"
#include "font_OpenSans.h"
#include "font_DroidSans.h"
#include "font_Michroma.h"
#include "font_Crystal.h"
#include "font_ChanceryItalic.h"
#endif
UNOR4WMatrixGFX display;

void setup() {
  while (!Serial && millis() < 5000)
    ;
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n\nMatrix GFX class test program");

  // Start the display, without library printing any debug information
  //display.begin();

  // use this version if you want the library to print out debug information
  display.begin(10, &Serial);
}

void loop() {
  test_draw_font_char(nullptr, "built-in");
#ifdef USE_ILI_FONT_LIBRARY
  nextPage();
  test_draw_font_char(&Chancery_9_Italic, "Chancery_9_Italic");
  nextPage();
  test_draw_font_char(&DroidSans_8, "DroidSans_8");
  nextPage();
  test_draw_font_char(&ComicSansMS_8, "ComicSansMS_8");
  nextPage();
  test_draw_font_char(&Crystal_8_Italic, "Crystal_8_Italic");
#endif
  nextPage();
  test_draw_font_char(&Arial_8, "Arial_8");
  nextPage();
}

GFXcanvas8 canvas(24, 8);  // 1-bit, 80x8 pixels

void test_draw_font_char(const ILI9341_t3_font_t *font, const char *name) {
  Serial.println(name);
  display.setILIFont(font);

  canvas.fillScreen(0);  // Clear canvas (not display)

  display.setTextColor(MATRIX_WHITE);  // Draw white text
  display_scroll_char(font, '<', MATRIX_WHITE);
  while (*name) {
    display_scroll_char(font, *name++, MATRIX_LIGHT);
  }
  display_scroll_char(font, '>', MATRIX_WHITE);
  display_scroll_char(font, ' ', MATRIX_WHITE);

  for (char i = ' '; i < '~'; i++) {
    display_scroll_char(font, i, MATRIX_WHITE);
  }
  display.setILIFont(nullptr);
  //display.setFont();
}

void display_scroll_char(const ILI9341_t3_font_t *font, char ch, uint16_t color) {
  canvas.setCursor(12, 0);
  canvas.setTextColor(color);

  drawILIFontChar(&canvas, font, false, color, ch);
  //  canvas.write(ch);
  int char_width = canvas.getCursorX() - 12;
  for (; char_width > 0; char_width -= 2) {
    ScrollCanvasLeft(canvas, 2, MATRIX_BLACK);
    writeOffsetRect(canvas, 0, 0);
    display.display();
    delay(125);
  }
}

void ScrollCanvasLeft(GFXcanvas8 &canvas, int scroll_count, uint16_t color_fill) {
  int x;
  for (x = 0; x < (canvas.width() - scroll_count); x++) {
    for (int y = 0; y < 8; y++) {
      canvas.writePixel(x, y, canvas.getPixel(x + scroll_count, y));
    }
  }
  canvas.fillRect(x, 0, scroll_count, 8, color_fill);
}


void writeOffsetRect(GFXcanvas8 &canvas, int x_offset, int y_offset) {
  display.clearDisplay();
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 12; x++) {
      uint8_t color;
      if ((color = canvas.getPixel(x + x_offset, y + y_offset))) {
        display.drawPixel(x, y, color);
      }
    }
  }
}

bool pause_between_pages = true;
void nextPage() {
  int ch;
  if (pause_between_pages) {
    Serial.println("Press anykey to continue");
    while ((ch = Serial.read()) == -1)
      ;

    if (ch == '$') {
      pause_between_pages = false;
      Serial.println("*** Pausing between pages disabled ***");
    }
    while (Serial.read() != -1)
      ;
  } else {
    ch = Serial.read();
    if (ch == '$') {
      pause_between_pages = true;
      Serial.println("*** Pausing between pages enabled ***");
      while (Serial.read() != -1)
        ;
      while ((ch = Serial.read()) == -1)
        ;
    }
    while (Serial.read() != -1)
      ;
  }
  display.clearDisplay();
  display.setCursor(0, 0);
}
