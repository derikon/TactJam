#ifndef _TACTJAM_OLED_
#define _TACTJAM_OLED_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

namespace tactjam {
namespace display {

class OLED_i2c {
  private:
    Adafruit_SSD1306* SSD1306_;
    uint8_t width_;
    uint8_t height_;
    uint8_t reset_pin_;
    uint8_t address_;
    bool initialized_;

  public:
    OLED_i2c() {
      width_ = 128;
      height_ = 64;
      reset_pin_ = 4;
      address_ = 0x3C;
      initialized_ = false;
      SSD1306_ = new Adafruit_SSD1306(width_, height_, &Wire, reset_pin_);
    }

    ~OLED_i2c() {
      SSD1306_->~Adafruit_SSD1306();
      SSD1306_ = nullptr;
    }

    bool Initialize() {
      initialized_ = SSD1306_->begin(SSD1306_SWITCHCAPVCC, address_);
      return initialized_;
    }

    void TestStaticScreen() {
      // lazy evaltuation shoul prevent call to Initialize if already initialized
      if (!initialized_ && !Initialize()) {
        return;
      }
      SSD1306_->clearDisplay();
      SSD1306_->invertDisplay(false);
      SSD1306_->setTextColor(SSD1306_WHITE);
      SSD1306_->setTextSize(1);
      SSD1306_->setCursor(0,0);
      SSD1306_->println("TactJam v0.0.1");
      SSD1306_->setCursor(0,10);
      SSD1306_->println("test screen");
      SSD1306_->display();
    }

    void TestDrawLines() {
      // lazy evaltuation shoul prevent call to Initialize if already initialized
      if (!initialized_ && !Initialize()) {
        return;
      }
      int16_t i;
      static const int16_t step = 4;
      SSD1306_->clearDisplay();
      for(i=0; i<width_; i+=step) {
        SSD1306_->drawLine(0, 0, i, height_-1, SSD1306_WHITE);
        SSD1306_->display();
        delay(1);
      }
      for(i=height_; i>=0; i-=step) {
        SSD1306_->drawLine(0, 0, width_-1, i, SSD1306_WHITE);
        SSD1306_->display();
        delay(1);
      }
      delay(250);
      SSD1306_->clearDisplay();
      SSD1306_->display();
    }
};

}
}

#endif //_TACTJAM_OLED_
