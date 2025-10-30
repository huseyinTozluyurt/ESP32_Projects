# ESP32 + SSD1306 OLED — Shapes Demo

A minimal, well-structured ESP32 sketch that uses **Adafruit_GFX** + **Adafruit_SSD1306** to draw basic shapes on a 128×64 I²C OLED.
Each “scene” (title + shape) is shown for 1500 ms, then the screen is cleared before the next scene.

> Works great as a starting template for your own OLED UI experiments.

---

## ✨ Features

* Clean **frame → pause → clear** cycle via a helper (`showAndPause`)
* Demonstrates: rectangle, filled rectangle, circle, filled circle, line, triangle, and rounded rectangle
* I²C at 400 kHz for snappy updates
* Clear, configurable pin/size/address defines

---

## 🧩 Hardware

* **Board:** ESP32 (any common dev-kit)
* **Display:** 0.96″ or 1.3″ SSD1306 OLED, **I²C** interface (usually address **0x3C**)

### Wiring (I²C)

| ESP32 Pin   | OLED Pin |
| ----------- | -------- |
| 3V3         | VCC      |
| GND         | GND      |
| GPIO **21** | SDA      |
| GPIO **22** | SCL      |

> You can change pins in the code with `I2C_SDA_PIN` and `I2C_SCL_PIN`.

---

## 📦 Libraries

Install from **Arduino Library Manager**:

* `Adafruit GFX Library`
* `Adafruit SSD1306`
* `Wire` (included with ESP32 core)

**Board support:** install *ESP32 by Espressif Systems* in **Boards Manager**.

---

## 🛠️ How to Build (Arduino IDE)

1. **Tools → Board:** pick your ESP32 model (e.g., *ESP32 Dev Module*).
2. **Select Board as (file -> preferences -> addional board manager url)** and paste https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json 
3. Go to Select Board section from Arduino IDE and select **ESP32 Dev Module**
4.  **Sketch → Include Library → Manage Libraries…**
   Install **Adafruit GFX** and **Adafruit SSD1306**.
5. **Copy** the code below into a new sketch and **Upload**.

```cpp
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
    for(;;); // init failed
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
  display.setCursor(0, 0);
  display.println(F("Filled Rect"));
  display.fillRect(34, 20, 60, 30, SSD1306_WHITE);
  showAndPause();

  // 3) Circle
  display.setCursor(0, 0);
  display.println(F("Circle"));
  display.drawCircle(64, 36, 18, SSD1306_WHITE);
  showAndPause();

  // 4) Filled Circle
  display.setCursor(0, 0);
  display.println(F("Filled Circle"));
  display.fillCircle(64, 36, 18, SSD1306_WHITE);
  showAndPause();

  // 5) Line
  display.setCursor(0, 0);
  display.println(F("Line"));
  display.drawLine(0, 32, 127, 32, SSD1306_WHITE);
  showAndPause();

  // 6) Triangle
  display.setCursor(0, 0);
  display.println(F("Triangle"));
  display.drawTriangle(32, 52, 96, 52, 64, 12, SSD1306_WHITE);
  showAndPause();

  // 7) Round Rect
  display.setCursor(0, 0);
  display.println(F("Round Rect"));
  display.drawRoundRect(20, 18, 88, 36, 8, SSD1306_WHITE);
  showAndPause();
}
```

---

## ⚙️ Configuration

* **Display size:**
  Change `SCREEN_WIDTH`, `SCREEN_HEIGHT` if your panel is different (e.g., 128×32).
* **I²C pins (ESP32):**
  `I2C_SDA_PIN` / `I2C_SCL_PIN` default to **21/22** here; adjust if needed.
* **I²C frequency:**
  `I2C_FREQ` is **400 kHz**. If your wiring is long/noisy, try `100000`.
* **I²C address:**
  Most SSD1306 I²C modules use **0x3C**. If yours is **0x3D**, change it in `display.begin(..., 0x3D)`.

---

## 🧠 How the frame/clear timing works

A common pitfall is drawing, then calling `delay()` without flushing/clearing properly—this can leave the next frame “dirty” or appear frozen.
This template uses:

1. `display.display()` – push current buffer to the panel
2. `delay(ms)` – keep it on-screen
3. `display.clearDisplay()` – clear the **buffer**
4. `display.display()` – push the clear frame so the next scene starts clean

All that is wrapped in `showAndPause(ms)`.

---

## 🧪 Customizing the Demo

* Replace shape calls with your own UI widgets or bitmaps.
* Change the pause per scene: `showAndPause(750)` for faster cycling.
* Add fonts: `setTextSize(2)` or custom fonts via Adafruit GFX font support.

---

## 🔍 Troubleshooting

* **Nothing on screen**

  * Confirm **VCC = 3.3 V**, **GND**, **SDA→21**, **SCL→22**.
  * Scan I²C to verify address (0x3C vs 0x3D).
  * Ensure you selected the correct **ESP32 board** in Arduino IDE.
* **Garbled / flickering**

  * Lower I²C speed to `100000`.
  * Keep wires short; add 4.7 kΩ pull-ups on SDA/SCL if your module lacks them.
* **Only text, no shapes**

  * Make sure **Adafruit_GFX** is installed alongside **Adafruit_SSD1306**.

---

## 🖼️ Bitmaps (optional)

You can render logos/icons by converting images to 1-bit bitmaps for Adafruit GFX. Popular tools include:

* “Image to C array” converters for Adafruit GFX (search for *Adafruit GFX bitmap converter*).
* Online SSD1306 bitmap generators (search for *OLED bitmap converter SSD1306*).

> Tip: Keep images small and high-contrast; 1-bit dithering helps.

---

## 📁 Project Structure (suggested)

```
esp32-oled-shapes/
├─ README.md
├─ src/
│  └─ main.ino
└─ lib/         # (optional, for local libs)
```

---

## 📜 License

This example is provided under the **MIT License**.
Feel free to use, modify, and share.

---

## 🙌 Credits

* Based on **Adafruit GFX** and **Adafruit SSD1306** libraries
* OLED graphics ideas from the maker community ✨

---

### ⭐ If this helped you…

Give the repo a star and share a photo/GIF of your OLED running the demo!
