#include "Pokerobo_Car.h"

#if (CONTROLLER == CONTROLLER_RF24)
const uint64_t address = 0x18580901LL;
RF24Listener rf24Listener(address);
#endif

#if (CONTROLLER_ROBOCAR)
RoboCarHandler roboCarHandler;
MovingResolver movingResolver;
#endif

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalHandler* pedestalHandlers[PEDESTALS_MAX] = {
  &pedestalHandler1,
  &pedestalHandler3,
};

PedestalGroup pedestalGroup(pedestalHandlers);

EventDispatcher eventDispatcher;

#if (CONTROLLER == CONTROLLER_RF24)
HangingDetector hangingDetector;
#endif

void setup() {
  Serial.begin(57600);

  #if (CONTROLLER_ROBOCAR)
  roboCarHandler.begin();
  roboCarHandler.set(&movingResolver);
  eventDispatcher.set(&roboCarHandler);
  #endif

  pedestalGroup.begin();
  eventDispatcher.set(&pedestalGroup);

  #if (CONTROLLER == CONTROLLER_RF24)
  hangingDetector.begin([] (void ()) {
    #if (CONTROLLER_ROBOCAR)
    roboCarHandler.stop();
    #endif
  }, 100);
  #endif

  #if (CONTROLLER == CONTROLLER_RF24)
  rf24Listener.begin();
  rf24Listener.set(&hangingDetector);
  rf24Listener.set(&eventDispatcher);
  #endif
}

void loop() {
  uint32_t begin = millis();

  eventDispatcher.loop();

  #if (CONTROLLER == CONTROLLER_RF24)
  rf24Listener.loop();
  #endif

  uint32_t exectime = millis() - begin;
  // Serial.print("EXECTIME"), Serial.print(": "), Serial.print(exectime), Serial.println();
  delay(max(100 - exectime, 0));
}
