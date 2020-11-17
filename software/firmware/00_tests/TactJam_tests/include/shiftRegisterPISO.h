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
  const uint8_t latchPinPISO = 16;
  const uint8_t clockPinPISO = 17;
  const uint8_t dataPinPISO = 4;

  bool initializedPISO = false;

  void SetupPISO() {
    pinMode(latchPinPISO, OUTPUT);
    pinMode(clockPinPISO, OUTPUT);
    pinMode(dataPinPISO, INPUT);
    initializedPISO = true;
  }

  uint8_t ReadFromPISO() {
    if (!initializedPISO) {
      return 0;
    }
    digitalWrite(latchPinPISO, LOW);
    digitalWrite(clockPinPISO, LOW);
    digitalWrite(clockPinPISO, HIGH);
    digitalWrite(latchPinPISO, HIGH);
    uint8_t data = 0;
    for(uint8_t j = 0; j < 8; j++) {
      uint8_t pinVal = digitalRead(dataPinPISO);
      if (!pinVal) {
        uint8_t a = (1 << j);
        data = data | a;
      }
      digitalWrite(clockPinPISO, LOW);
      digitalWrite(clockPinPISO, HIGH);
    }
    return data;
  }
}
}
#endif //_TACTJAM_SHIFTREGISTER_PISO_
