#ifndef _TACTJAM_SHIFTREGISTER_SIPO_
#define _TACTJAM_SHIFTREGISTER_SIPO_

/*
 * A shift register is used to reduce the number of pins
 * for driving 8 LEDs. The values of all LEDs can be stored
 * in a single 8-bit data type (e.g. uint8_t).
 * Order of LEDs:
 *  | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
 * 
 */

#include <Arduino.h>

namespace tactjam {
namespace shiftregister {
  const uint8_t latchPinSIPO = 18;
  const uint8_t clockPinSiPO = 19;
  const uint8_t dataPinSIPO = 5;
  const uint8_t bitOrderSIPO = MSBFIRST;
  const uint32_t delayMillis = 100;

  bool initializedSIPO = false;

  void SetupSIPO() {
    pinMode(latchPinSIPO, OUTPUT);
    pinMode(clockPinSiPO, OUTPUT);
    pinMode(dataPinSIPO, OUTPUT);
    initializedSIPO = true;
  }

  void UpdateSIPO(uint8_t value) {
    if (!initializedSIPO) {
      return;
    }
    digitalWrite(latchPinSIPO, LOW);
    shiftOut(dataPinSIPO, clockPinSiPO, bitOrderSIPO, value);
    digitalWrite(latchPinSIPO, HIGH);
  }

  void TestSIPO() {
    if (!initializedSIPO) {
      return;
    }
    for (uint8_t i=0; i<255; i++) {
      UpdateSIPO(i);
      delay(delayMillis);
    }
    UpdateSIPO(0);
  }
}
}

#endif //_TACTJAM_SHIFTREGISTER_SIPO_
