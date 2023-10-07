#include <UNOR4WMatrixGFX.h>
#include <Fonts/FreeMono9pt7b.h>
#include <UNOR4W_matrix_font_Arial89.h>

UNOR4WMatrixGFX display;

void setup() {
  while (!Serial && millis() < 5000)
    ;
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n\nMatrix GFX class test program");
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

#ifdef MATRIX_INT_PER_PIXEL
  display.begin(1);
#else
  display.begin(10);
#endif
  testPixels();  // Draw many lines

  Serial.print("Period Raw(100):"),
    Serial.println(display.s_ledTimer.get_period_raw(), DEC);

  testdrawline();

  testdrawrect(MATRIX_WHITE);  // Draw rectangles (outlines)
  testdrawrect(MATRIX_LIGHT);  // Draw rectangles (outlines)
  testdrawrect(MATRIX_DARK);   // Draw rectangles (outlines)
  testdrawrect(MATRIX_LIGHT);  // Draw rectangles (outlines)
  testdrawrect(MATRIX_WHITE);  // Draw rectangles (outlines)

  testfillrect();  // Draw rectangles (filled)
  testILIFonts();

  testdrawchar();
  // Test draw GFX Font - 
  // currently disabled as GFX fonts have issues.
  //testdrawfontchar();
}

uint8_t loop_count = 0;
void loop() {
  loop_count++;
  testcanvasscrolltext();
}

void testPixels() {
  for (uint8_t y = 0; y < 8; y++) {
    for (uint8_t x = 0; x < 12; x++) {
      display.drawPixel(x, y, MATRIX_WHITE);
      display.display();
      delay(25);
    }
  }
}

void testdrawline() {
  int16_t i;

  display.clearDisplay();  // Clear display buffer

  for (i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, MATRIX_WHITE);
    display.display();  // Update screen with each newly-drawn line
    delay(500);
  }
  for (i = 0; i < display.height(); i += 4) {
    display.drawLine(0, 0, display.width() - 1, i, MATRIX_WHITE);
    display.display();
    delay(500);
  }
  delay(250);

  display.clearDisplay();

  for (i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, MATRIX_WHITE);
    display.display();
    delay(1);
  }
  for (i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, MATRIX_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for (i = display.width() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, i, 0, MATRIX_WHITE);
    display.display();
    delay(1);
  }
  for (i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, 0, i, MATRIX_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for (i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, MATRIX_WHITE);
    display.display();
    delay(1);
  }
  for (i = 0; i < display.width(); i += 4) {
    display.drawLine(display.width() - 1, 0, i, display.height() - 1, MATRIX_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);  // Pause for 2 seconds
}

void testdrawrect(uint8_t color) {
  display.clearDisplay();
  digitalWrite(4, HIGH);

  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, color);
    display.display();  // Update screen with each newly-drawn rectangle
    delay(500);
  }

  delay(2000);
  digitalWrite(4, LOW);
}

void testfillrect(void) {
  display.clearDisplay();
  uint8_t color = MATRIX_WHITE;
  digitalWrite(4, HIGH);
  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, color);
    display.display();  // Update screen with each newly-drawn rectangle
    color = (color == MATRIX_WHITE) ? MATRIX_DARK : MATRIX_WHITE;
    delay(1);
  }

  delay(2000);
  digitalWrite(4, LOW);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(MATRIX_WHITE);  // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  display.cp437(true);                 // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for (int16_t i = 0; i < 256; i += 2) {
    display.clearDisplay();
    display.setCursor(0, 0);  // Start at top-left corner
    if (i == '\n') display.write(' ');
    else display.write(i);
    if ((i + 1) == '\n') display.write(' ');
    else display.write(i + 1);
    display.display();
    delay(125);
  }
}

void testdrawfontchar(void) {
  display.clearDisplay();
  display.setRotation(1);
  display.setFont(&FreeMono9pt7b);
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(MATRIX_WHITE);  // Draw white text

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for (int16_t i = ' '; i < '~'; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);  // Start at top-left corner
    display.write(i);
    display.display();
    delay(125);
  }
  display.setFont();
  display.setRotation(0);
}

GFXcanvas8 canvas(80, 16);  // 1-bit, 80x8 pixels


void testcanvasscrolltext() {
  canvas.fillScreen(0);               // Clear canvas (not display)
  canvas.setCursor(0, 0);             // Pos. is BASE LINE when using fonts!
  canvas.setTextSize(1);              // Normal 1:1 pixel scale
  canvas.setTextColor(MATRIX_WHITE);  // Draw white text
  canvas.print("Scroll Text");
  uint8_t canvas_max_x = canvas.getCursorX();
  canvas.setTextColor(MATRIX_DARK);  // Draw white text
  canvas.print("\nSecond line");
  uint8_t cx2 = canvas.getCursorX();
  if (cx2 > canvas_max_x) canvas_max_x = cx2;
  canvas.println();
  uint8_t canvas_max_y = canvas.getCursorY();
  static bool first_call = true;

  if (first_call) {
    first_call = false;
    Serial.print("Canvas cursorX:");
    Serial.print(canvas_max_x, DEC);
    Serial.print(" y:");
    Serial.println(canvas_max_y, DEC);
  }


  int x_offset = 0;
  int y_offset = 0;

  // go out in x direction
  for (x_offset = 0; x_offset < (canvas_max_x - display.width()); x_offset++) {
    display.clearDisplay();
    writeOffsetRect(canvas, x_offset, y_offset);
    display.display();
    delay(50);
  }
  // go down in y direction
  x_offset--;
  for (y_offset = 0; y_offset < (canvas_max_y - display.height()); y_offset++) {
    display.clearDisplay();
    writeOffsetRect(canvas, x_offset, y_offset);
    display.display();
    delay(50);
  }
  y_offset--;
  // Back to the start in x
  for (; x_offset >= 0; x_offset--) {
    display.clearDisplay();
    writeOffsetRect(canvas, x_offset, y_offset);
    display.display();
    delay(50);
  }
  // Back to the start in y
  for (; y_offset >= 0; y_offset--) {
    display.clearDisplay();
    writeOffsetRect(canvas, x_offset, y_offset);
    display.display();
    delay(50);
  }
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

void testILIFonts() {
  //  display.setRotation(1);  // lets try doing this where we can display larger font
  display.clearDisplay();

  //  display.setFont(&FreeMono9pt7b);
  // display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(MATRIX_WHITE);  // Draw white text

  for (uint8_t rot = 0; rot < 4; rot++) {
    if (rot & 1) display.setILIFont(&Arial_9);
    else display.setILIFont(&Arial_8);
    Serial.print("Try rotation: ");
    Serial.println(rot, DEC);
    display.setRotation(rot);
    Serial.println(display.getRotation(), DEC);

    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    for (int16_t i = 'A'; i <= 'E'; i++) {
      display.clearDisplay();
      display.setCursor(0, 0);  // Start at top-left corner
      display.setTextWrap(false);
      display.write(i);
      display.display();
      delay(1000);
    }
    //Serial.println("Press any key to continue");
    //while (Serial.read() == -1);
    //while (Serial.read() != -1);
  }
  display.setILIFont(nullptr);
  display.setRotation(0);  // lets try doing this where we can display larger font
  //display.setFont();
}
