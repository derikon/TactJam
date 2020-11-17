#ifndef _TACTJAM_OLED_
#define _TACTJAM_OLED_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

namespace tactjam {
namespace display {
  const uint8_t width = 128;
  const uint8_t height = 64;
  const uint8_t reset_pin = 4;
  const uint8_t i2cAddress = 0x3C;

  Adafruit_SSD1306 oled(width, height, &Wire, reset_pin);
  static bool initialized = false;

  bool SetupOLED() {
    initialized = oled.begin(SSD1306_SWITCHCAPVCC, i2cAddress);
    return initialized;
  }

  void TestStaticScreen() {
    if (!initialized) {
      return;
    }
    oled.clearDisplay();
    oled.invertDisplay(false);
    oled.setTextColor(SSD1306_WHITE);
    oled.setTextSize(1);
    oled.setCursor(0,0);
    oled.println("TactJam v0.0.1");
    oled.setCursor(0,10);
    oled.println("test screen");
    oled.display();
  }

  void TestDrawLine() {
    if (!initialized) {
      return;
    }
    int16_t i;
    static const int16_t step = 4;
    oled.clearDisplay();
    for(i=0; i<width; i+=step) {
      oled.drawLine(0, 0, i, height-1, SSD1306_WHITE);
      oled.display();
      delay(1);
    }
    for(i=height; i>=0; i-=step) {
      oled.drawLine(0, 0, width-1, i, SSD1306_WHITE);
      oled.display();
      delay(1);
    }
    delay(250);
    oled.clearDisplay();
    oled.display();
}

}
}

#endif //_TACTJAM_OLED_
