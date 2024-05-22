#include "Pokerobo_Car.h"

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

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Starting");
  #endif

  pedestalGroup.begin();
  eventDispatcher.set(&pedestalGroup);

  ps2Controller.begin();
  ps2Controller.set(&eventDispatcher);

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Done!");
  #endif
}

void loop() {
  uint32_t begin = millis();

  // eventDispatcher.loop();

  ps2Controller.loop();

  uint32_t exectime = millis() - begin;
  delay(max(200 - exectime, 0));
}
