#ifndef _TACTJAM_BUZZER_
#define _TACTJAM_BUZZER_

#include <Arduino.h>

namespace tactjam {
namespace buzzer {
  const uint8_t pin = 23;
  const uint8_t pwmChannel = 0;
  const uint32_t duration = 300;


  void NoTone(uint32_t duration = duration) {
      ledcDetachPin(pin);
      ledcWrite(pwmChannel, 0);
      delay(duration);
  }

  void Tone(double frequency, uint32_t duration = duration) {
      if (ledcRead(pwmChannel)) {
          return;
      }
      ledcAttachPin(pin, pwmChannel);
      ledcWriteTone(pwmChannel, frequency);
      if (duration>1) {
          delay(duration);
          NoTone(0);
      }    
  }

  void TestMelody() {
    Tone(600);
    NoTone();
    Tone(300);
    NoTone();
    Tone(600);
    NoTone();
    Tone(600);
    NoTone(100);
    Tone(600);
    NoTone(100);
  }
}
}

#endif //_TACTJAM_BUZZER_
