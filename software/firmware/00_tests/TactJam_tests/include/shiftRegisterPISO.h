#ifndef _TACTJAM_SHIFTREGISTER_PISO_
#define _TACTJAM_SHIFTREGISTER_PISO_

/*
 * A shift register is used to reduce the number of pins
 * for reading 8 buttons. The values of all buttons can be
 * stored in a single 8-bit data type (e.g. uint8_t).
 * Order of buttons:
 *  | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
 * 
 */

#include <Arduino.h>

namespace tactjam {
namespace shiftregister {
namespace piso {

class M74HC166 {
  private:
    uint8_t latch_pin_;
    uint8_t clock_pin_;
    uint8_t data_pin_;
    uint8_t data_8_;
    uint16_t data_16_;
    bool initialized_;

  public:
    M74HC166() {
      // default configuration M74HC166(16, 17, 4)
      *this = M74HC166(33, 32, 25);
    }

    M74HC166(uint8_t latch_pin, uint8_t clock_pin, uint8_t data_pin) {
      latch_pin_ = latch_pin;
      clock_pin_ = clock_pin;
      data_pin_ = data_pin;
      initialized_ = false;
    }

    void ChangePins(uint8_t latch_pin, uint8_t clock_pin, uint8_t data_pin) {
      latch_pin_ = latch_pin;
      clock_pin_ = clock_pin;
      data_pin_ = data_pin;
      Initialize();
    }

    void Initialize() {
      pinMode(latch_pin_, OUTPUT);
      pinMode(clock_pin_, OUTPUT);
      pinMode(data_pin_, INPUT);
      initialized_ = true;
    }

    uint8_t Read8() {
      if (!initialized_) {
        Initialize();
      }
      digitalWrite(latch_pin_, LOW);
      digitalWrite(clock_pin_, LOW);
      digitalWrite(clock_pin_, HIGH);
      digitalWrite(latch_pin_, HIGH);
      data_8_ = 0;
      for(uint8_t j = 0; j < 8; j++) {
        if (!digitalRead(data_pin_)) {
          bitSet(data_8_, j);
          //data_8_ = data_8_ | (uint8_t)((uint8_t)1 << j);
        }
        digitalWrite(clock_pin_, LOW);
        digitalWrite(clock_pin_, HIGH);
      }
      return data_8_;
    }

    uint16_t Read16() {
      if (!initialized_) {
        Initialize();
      }
      digitalWrite(latch_pin_, LOW);
      digitalWrite(clock_pin_, LOW);
      digitalWrite(clock_pin_, HIGH);
      digitalWrite(latch_pin_, HIGH);
      data_16_ = 0;
      for(uint8_t j = 0; j < 16; j++) {
        if (!digitalRead(data_pin_)) {
          bitSet(data_16_, j);
          //data_16_ = data_16_ | (uint16_t)((uint16_t)1 << j);
        }
        digitalWrite(clock_pin_, LOW);
        digitalWrite(clock_pin_, HIGH);
      }
      return data_16_;
    }
};

}
}
}

#endif //_TACTJAM_SHIFTREGISTER_PISO_
