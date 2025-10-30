#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== OLED configuration =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
#define I2C_SDA_PIN  21
#define I2C_SCL_PIN  22
#define I2C_FREQ     400000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Show current buffer, wait, then clear screen and flush the clear
void showAndPause(uint16_t ms = 1500) {
  display.display();         // push current frame
  delay(ms);                 // pause
  display.clearDisplay();    // clear buffer
  display.display();         // flush the clear so next frame starts clean
}

void setup() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQ);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Optional debug
    // Serial.begin(115200); Serial.println(F("SSD1306 init failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // 0) Title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("ESP32 + OLED"));
  display.println(F("Shapes Demo"));
  showAndPause();  // 1500 ms

  // 1) Rectangle
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Rectangle"));
  display.drawRect(10, 20, 60, 30, SSD1306_WHITE);
  showAndPause();

  // 2) Filled Rectangle
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Filled Rect"));
  display.fillRect(34, 20, 60, 30, SSD1306_WHITE);
  showAndPause();

  // 3) Circle
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Circle"));
  display.drawCircle(64, 36, 18, SSD1306_WHITE);
  showAndPause();

  // 4) Filled Circle
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Filled Circle"));
  display.fillCircle(64, 36, 18, SSD1306_WHITE);
  showAndPause();

  // 5) Line
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Line"));
  display.drawLine(0, 32, 127, 32, SSD1306_WHITE);
  showAndPause();

  // 6) Triangle
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Triangle"));
  display.drawTriangle(32, 52, 96, 52, 64, 12, SSD1306_WHITE);
  showAndPause();

  // 7) Round Rect
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Round Rect"));
  display.drawRoundRect(20, 18, 88, 36, 8, SSD1306_WHITE);
  showAndPause();

}
