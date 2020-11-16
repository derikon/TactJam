#include <Arduino.h>

// uncomment the parts you want to include
#define TACTJAM_TEST_OLED



#ifdef TACTJAM_TEST_OLED
#include "oled.h"
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
    Serial.println("ERROR: display setup");
  }
  tactjam::display::TestStaticScreen();
  delay(10000);
#endif
}

void loop() {
#ifdef TACTJAM_TEST_OLED
  tactjam::display::TestDrawLine();
#endif
}