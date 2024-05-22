#include "Pokerobo_Car.h"

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalHandler* pedestalHandlers[PEDESTALS_MAX] = {
  &pedestalHandler1,
  &pedestalHandler3,
};

PedestalGroup pedestalGroup(pedestalHandlers);

void onLeftJoystickChanged(int nJoyX, int nJoyY) {
  nJoyX = map(nJoyX, -255, 255, 5, -5);
  nJoyY = map(nJoyY, -255, 255, 5, -5);
  pedestalGroup.changeByJoystick(nJoyX, nJoyY);
}

PS2Listener ps2Controller;
PS2EventDispatcher eventDispatcher;

void setup() {
  Serial.begin(57600);

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Starting");
  #endif

  pedestalGroup.begin();

  eventDispatcher.setOnLeftJoystickChanged(onLeftJoystickChanged);

  ps2Controller.begin();
  ps2Controller.set(&eventDispatcher);

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Done!");
  #endif
}

void loop() {
  uint32_t begin = millis();

  ps2Controller.loop();

  uint32_t exectime = millis() - begin;
  delay(max(200 - exectime, 0));
}
