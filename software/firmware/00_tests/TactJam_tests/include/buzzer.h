#ifndef _TACTJAM_BUZZER_
#define _TACTJAM_BUZZER_

#include <Arduino.h>

namespace tactjam {

class Buzzer {
  private:
    uint8_t pin_;
    uint8_t pwm_channel_;

  public:
    Buzzer() {
      // default configuration
      *this = Buzzer(23, 0);
    }

    Buzzer(uint8_t pin, uint8_t pwm_channel) {
      pin_ = pin;
      pwm_channel_ = pwm_channel;
    }

    ~Buzzer() = default;

    void NoTone(uint32_t length) {
        ledcDetachPin(pin_);
        ledcWrite(pwm_channel_, 0);
        delay(length);
    }

    void Tone(double frequency, uint32_t length) {
        if (ledcRead(pwm_channel_)) {
            return;
        }
        ledcAttachPin(pin_, pwm_channel_);
        ledcWriteTone(pwm_channel_, frequency);
        if (length>1) {
            delay(length);
            NoTone(0);
        }    
    }

    void TestMelody() {
      Tone(700, 100);
      NoTone(50);
      Tone(600, 100);
      NoTone(50);
      Tone(500, 100);
      NoTone(50);
      Tone(400, 100);
      NoTone(50);
      Tone(300, 100);
      NoTone(50);
      Tone(500, 300);
      NoTone(100);
      Tone(500, 300);
      NoTone(100);
      Tone(500, 300);
      NoTone(100);
    }
};

}

#endif //_TACTJAM_BUZZER_
