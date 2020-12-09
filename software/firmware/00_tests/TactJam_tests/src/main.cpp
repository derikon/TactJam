#include <Arduino.h>
#include <vector>

// uncomment the parts you want to include
//#define TACTJAM_TEST_OLED
//#define TACTJAM_TEST_BUZZER
#define TACTJAM_TEST_ESPCONFIG
//#define TACTJAM_TEST_SIPO
//#define TACTJAM_TEST_PISO
//#define TACTJAM_TEST_I2CSCAN
//#define TACTJAM_TEXT_PWMMULTIPLEXER
//#define TACTJAM_TEST_LIN_ENCODER
//#define TACTJAM_TEST_DECODE_VTP
//#define TACTJAM_TEST_VTP_PLAYER




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
#ifdef TACTJAM_TEXT_PWMMULTIPLEXER
#include "pwmMultiplxer.h"
tactjam::pwm::PWMPCA9685 actuators;
#endif
#ifdef TACTJAM_TEST_LIN_ENCODER
#include "linEncoder.h"
tactjam::encoder::LinEncoder intensity_encoder(12, 30);
tactjam::encoder::LinEncoderSwitch mode_encoder(14, 4);
tactjam::encoder::LinEncoderSwitch slot_encoder(27, 3);
#endif
#ifdef TACTJAM_TEST_DECODE_VTP
#include "data_format/vtpDecoder.h"
tactjam::data_format::VTPDecoder vtp_decoder;
#endif
#ifdef TACTJAM_TEST_VTP_PLAYER
#include "data_format/vtpPlayer.h"
tactjam::data_format::VTPPlayer vtp_player(20);
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
  oled_display.TestMenuScreen();
#endif
#ifdef TACTJAM_TEST_BUZZER
  Serial.println("\tBuzzer");
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
#ifdef TACTJAM_TEXT_PWMMULTIPLEXER
  Serial.println("\tPWM Multiplexer");
  actuators.Initialize();
  actuators.Test();
#endif
#ifdef TACTJAM_TEST_LIN_ENCODER
  Serial.println("\tLinear Encoder");
  intensity_encoder.Initialize();
  mode_encoder.Initialize();
  slot_encoder.Initialize();
#endif
#ifdef TACTJAM_TEST_DECODE_VTP
  delay(5000);
  Serial.println("\tVTP Decoder");
  vtp_decoder.DecodeExample();
#endif
#ifdef TACTJAM_TEST_VTP_PLAYER
  delay(5000);
  Serial.println("\tVTP Player");
  vtp_player.Initialize();
#endif
}


void loop() {
#ifdef TACTJAM_TEST_PISO
  //auto activeButtons = buttons_shiftregister.Read8();
  auto activeButtons = buttons_shiftregister.Read16();
  auto activeActuatorButtons = activeButtons >> 8;
  if (activeActuatorButtons != 0) {
    Serial.print("activeActuatorButtons DEC: ");
    Serial.println(activeActuatorButtons, DEC);
    Serial.print("activeActuatorButtons BIN: ");
    Serial.println(activeActuatorButtons, BIN);
  }
  uint8_t activeMenuButtons = (activeButtons >> 4) & 0xF;
  if (activeMenuButtons != 0) {
    Serial.print("activeMenuButtons DEC: ");
    Serial.println(activeMenuButtons, DEC);
    Serial.print("activeMenuButtons BIN: ");
    Serial.println(activeMenuButtons, BIN);
  }
#ifdef TACTJAM_TEST_SIPO
  led_shiftregister.Update(activeButtons);
#endif
#ifdef TACTJAM_TEXT_PWMMULTIPLEXER
  actuators.Update(activeButtons);
#endif //TACTJAM_TEXT_PWMMULTIPLEXER
#endif //TACTJAM_TEST_PISO
#ifdef TACTJAM_TEST_I2CSCAN
  i2c_scanner.Scan();
  delay(3000);
#endif
#ifdef TACTJAM_TEST_LIN_ENCODER
  if (intensity_encoder.UpdateAvailable()) {
    delay(5);
    Serial.printf("global intensity: %d (12bit), %d (8bit), %d (percent)\n", intensity_encoder.Get12bit(), intensity_encoder.Get8bit(), intensity_encoder.GetPercent());
  }
  if (mode_encoder.UpdateAvailable()) {
    delay(20);
    Serial.printf("mode: %d\n", mode_encoder.GetState());
  }
  if (slot_encoder.UpdateAvailable()) {
    delay(20);
    Serial.printf("slot: %d\n", slot_encoder.GetState());
  }
#endif
#ifdef TACTJAM_TEST_VTP_PLAYER
  vtp_player.GetNextSample();
  vtp_player.PrintSample();
  vtp_player.WaitUntilNextTick();
#endif
#ifdef TACTJAM_TEST_ESPCONFIG
  tactjam::config::MonitorHeapSize();
  static std::vector<byte*> memory_grave;
  static int heap_iterations = 0;
  heap_iterations++;
  auto evil_mem = new byte[666];
  memory_grave.push_back(evil_mem);
  if (heap_iterations == 100) {
    Serial.println("free wasted heap");
    for (auto item : memory_grave) {
      delete(item);
    }
    memory_grave.clear();
    heap_iterations = 0;
  }
  delay(200);
#endif
}
