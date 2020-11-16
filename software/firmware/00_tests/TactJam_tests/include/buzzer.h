#ifndef _TACTJAM_BUZZER_
#define _TACTJAM_BUZZER_

#include <Arduino.h>

namespace tactjam {
namespace buzzer {
  const uint8_t pin = 23;
  const uint8_t pwmChannel = 0;
  const uint32_t duration = 300;


  void NoTone()
  {
      ledcDetachPin(pin);
      ledcWrite(pwmChannel, 0);
  }

  void Tone(double frequency, uint32_t duration = duration)
  {
      if (ledcRead(pwmChannel)) {
          return;
      }
      ledcAttachPin(pin, pwmChannel);
      ledcWriteTone(pwmChannel, frequency);
      if (duration>1) {
          delay(duration);
          NoTone();
      }    
  }

  void TestMelody() {
    Tone(600);
    delay(duration);
    Tone(300);
    delay(duration);
    Tone(600);
    delay(duration);
    Tone(600);
    delay(100);
    Tone(600);
    delay(100);
  }
}
}

#endif //_TACTJAM_BUZZER_
