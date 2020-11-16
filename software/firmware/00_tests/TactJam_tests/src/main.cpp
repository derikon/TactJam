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
  // you should see text on the display
  tactjam::display::TestStaticScreen();
  delay(10000);
  // you should see lines drawn one after another across the display
  tactjam::display::TestDrawLine();
#endif
}

void loop() {

}