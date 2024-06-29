#include "Pokerobo_Car.h"

DisplayAdapter displayAdapter;

const uint64_t address = 0x18580900LL + 1;
RF24Listener rf24Listener(address);
HangingDetector hangingDetector;

MovingResolver movingResolver;
RoboCarHandler roboCarHandler(&movingResolver);

RemoteControlCar remoteControlCar("Remote Control Car",
    &displayAdapter, &roboCarHandler);

ProgramManager programManager(&rf24Listener,
    &displayAdapter, &hangingDetector);

void setup() {
  Serial.begin(57600);

  displayAdapter.begin();

  roboCarHandler.begin();

  hangingDetector.begin([] (void ()) {
    displayAdapter.clear();
    displayAdapter.render(0, 0, "Suspending...");
    roboCarHandler.stop();
  }, 10);

  rf24Listener.begin();

  remoteControlCar.begin();

  programManager.add(&remoteControlCar);
  programManager.begin();
}

void loop() {
  uint32_t begin = millis();
  programManager.check();
  delay(max(100 - (millis() - begin), 0));
}
