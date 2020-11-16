#include <Arduino.h>

// uncomment the parts you want to include
#define TACTJAM_TEST_OLED
#define TACTJAM_TEST_BUZZER



#ifdef TACTJAM_TEST_OLED
#include "oled.h"
#endif
#ifdef TACTJAM_TEST_BUZZER
#include "buzzer.h"
#endif


const unsigned long baudRate = 115200;


void setup() {
  Serial.begin(baudRate);
  while (!Serial) {
    delay(5);
  }
  Serial.println("TactJam – Test Suite");
  Serial.println("incl.:");

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
}


void loop() {

}
