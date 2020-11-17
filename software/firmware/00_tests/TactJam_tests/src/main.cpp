#include <Arduino.h>

// uncomment the parts you want to include
#define TACTJAM_TEST_OLED
#define TACTJAM_TEST_BUZZER
#define TACTJAM_TEST_ESPCONFIG
#define TACTJAM_TEST_SIPO



#ifdef TACTJAM_TEST_OLED
#include "oled.h"
#endif
#ifdef TACTJAM_TEST_BUZZER
#include "buzzer.h"
#endif 
#ifdef TACTJAM_TEST_ESPCONFIG
#include "espConfig.h"
#endif
#ifdef TACTJAM_TEST_SIPO
#include "shiftRegisterSIPO.h"
#endif




const unsigned long baudRate = 115200;


void setup() {
  Serial.begin(baudRate);
  while (!Serial) {
    delay(5);
  }
  Serial.println("TactJam – Test Suite");
  Serial.println("incl.:");
#ifdef TACTJAM_TEST_ESPCONFIG
  Serial.println("\tESP configurations");
  tactjam::config::DisableEspRadios();
#endif
#ifdef TACTJAM_TEST_OLED
  Serial.println("\tOLED display");
  if (!tactjam::display::SetupOLED()) {
    Serial.println("\tERROR: display setup");
  }
  tactjam::display::TestStaticScreen();
  delay(5000);
  tactjam::display::TestDrawLine();
#endif
#ifdef TACTJAM_TEST_BUZZER
  Serial.println("\tbuzzer");
  tactjam::buzzer::TestMelody();
#endif
#ifdef TACTJAM_TEST_SIPO
  Serial.println("\tShift Registers (SIPO)");
  tactjam::shiftregister::SetupSIPO();
  tactjam::shiftregister::TestSIPO();
#endif
}


void loop() {

}
