#include "PS2_Controller.h"

PS2Controller ps2Controller;

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalHandler* pedestalHandlers[PEDESTALS_MAX] = {
  &pedestalHandler1,
  &pedestalHandler3,
};

PedestalGroup pedestalGroup(pedestalHandlers);

EventDispatcher eventDispatcher;

void setup() {
  Serial.begin(57600);

  pedestalGroup.begin();
  eventDispatcher.set(&pedestalGroup);

  ps2Controller.begin();
  ps2Controller.set(&eventDispatcher);
}

void loop() {
  uint32_t begin = millis();

  // eventDispatcher.loop();

  ps2Controller.loop();

  uint32_t exectime = millis() - begin;
  delay(max(200 - exectime, 0));
}
