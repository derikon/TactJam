#include <Arduino.h>

// uncomment the parts you want to include
#define TACTJAM_TEST_OLED
#define TACTJAM_TEST_BUZZER
#define TACTJAM_TEST_ESPCONFIG
#define TACTJAM_TEST_SIPO
#define TACTJAM_TEST_PISO
#define TACTJAM_TEST_I2CSCAN



#ifdef TACTJAM_TEST_OLED
#include "oled.h"
tactjam::display::OLED_i2c oled_display;
#endif
#ifdef TACTJAM_TEST_BUZZER
#include "buzzer.h"
tactjam::Buzzer buzzer;
#endif 
#ifdef TACTJAM_TEST_ESPCONFIG
#include "espConfig.h"
#endif
#ifdef TACTJAM_TEST_SIPO
#include "shiftRegisterSIPO.h"
tactjam::shiftregister::sipo::SN74HC595 led_shiftregister;
#endif
#ifdef TACTJAM_TEST_PISO
#include "shiftregisterPISO.h"
tactjam::shiftregister::piso::M74HC166 buttons_shiftregister;
#endif
#ifdef TACTJAM_TEST_I2CSCAN
#include "i2cScan.h"
tactjam::i2c::Scanner i2c_scanner;
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
  if (!oled_display.Initialize()) {
    Serial.println("\tERROR: display setup");
  }
  oled_display.TestStaticScreen();
  delay(3000);
  oled_display.TestDrawLines();
#endif
#ifdef TACTJAM_TEST_BUZZER
  Serial.println("\tbuzzer");
  buzzer.TestMelody();
#endif
#ifdef TACTJAM_TEST_SIPO
  Serial.println("\tShift Registers (SIPO)");
  led_shiftregister.Initialize();
  led_shiftregister.Test();
#endif
#ifdef TACTJAM_TEST_PISO
  Serial.println("\tShift Registers (PISO)");
  buttons_shiftregister.Initialize();
#endif
#ifdef TACTJAM_TEST_I2CSCAN
  i2c_scanner.Initialize();
#endif
}


void loop() {
#ifdef TACTJAM_TEST_PISO
  uint8_t activeButtons = buttons_shiftregister.Read();
  if (activeButtons != 0) {
    Serial.print("activeButtons DEC: ");
    Serial.println(activeButtons, DEC);
    Serial.print("activeButtons BIN: ");
    Serial.println(activeButtons, BIN);
  }
#ifdef TACTJAM_TEST_SIPO
  led_shiftregister.Update(activeButtons);
#endif
#endif
#ifdef TACTJAM_TEST_I2CSCAN
  i2c_scanner.Scan();
  delay(3000);
#endif
}
