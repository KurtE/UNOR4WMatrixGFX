#include <UNOR4WMatrixGFX.h>

UNOR4WMatrixGFX display;

void setup() {
  while (!Serial && millis() < 5000) {}
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
}

uint8_t rotation = 0;
char rot_str[] = "0";
void loop() {
  Serial.print("Test Rotation: ");
  Serial.println(rotation, DEC);
  display.setRotation(rotation);

  rot_str[0] = '0' + rotation;
  display.clearDisplay();
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(rot_str, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((display.width() - w) / 2, (display.height() - h) / 2);
  display.setTextColor(MATRIX_WHITE);
  display.print(rot_str);
  print_display_info();
  display.display();
  step("Text");

  display.clearDisplay();
  display.drawRect(0, 0, display.width(), display.height(), MATRIX_WHITE);
  display.drawRect(1, 1, display.width() - 2, display.height() - 2, MATRIX_LIGHT);
  display.drawRect(2, 2, display.width() - 4, display.height() - 4, MATRIX_DARK);
  display.display();
  step("Rects");

  display.clearDisplay();
  for (uint8_t y = 0; y < display.height(); y += 2) {
    if ((y + 3) > display.width()) break;
    display.drawFastHLine(y, y, 3, MATRIX_WHITE);
  }
  display.display();
  step("HLine");

  display.clearDisplay();
  for (uint8_t x = 0; x < display.width(); x += 2) {
    if ((x + 3) > display.height()) break;
    display.drawFastVLine(x, x, 3, MATRIX_WHITE);
  }
  display.display();
  step("VLine");
  rotation = (rotation + 1) & 0x3;
}

void step(const char *szTitle) {
  Serial.print(szTitle);
  Serial.println(" *** Press any key to continue ***");
  while (Serial.read() == -1) {}
  while (Serial.read() != -1) {}
}

void print_display_info() {
  for (int i = 0; i < 11; i++) {
    Serial.print(i, DEC);
    for (int j = 0; j < 10; j++) {
      int8_t pin = UNOR4WMatrixGFX::matrix_irq_pins[i][j];
      if (pin == -1) break;
      uint8_t y = pin / 12;
      uint8_t x = pin - y * 12;
      uint16_t color = display.getPixel(x, y);
      if (color) {
        Serial.print(" ");
        Serial.print(pin);
        Serial.print(":");
        Serial.print(color, DEC);
      }
    }
    Serial.println();
  }
}