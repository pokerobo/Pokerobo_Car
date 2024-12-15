#include "Pokerobo_Car_speedometer.h"

const uint64_t address = 0x18580900LL + 1;

DisplayAdapter displayAdapter;
RF24Listener rf24Listener(address);
HangingDetector hangingDetector;

MovingResolver movingResolver;
RoboCarHandler roboCarHandler(&movingResolver);

SpeedometerWrapper speedometerAdapter;

RemoteControlCar remoteControlCar("Remote Control Car",
    &displayAdapter, &roboCarHandler, &speedometerAdapter);

ProgramManager programManager(&rf24Listener,
    &displayAdapter, &hangingDetector);

void setup() {
  Serial.begin(57600);

  pinMode(A0, INPUT_PULLUP);

  displayAdapter.begin();

  roboCarHandler.begin();

  speedometerAdapter.begin();

  hangingDetector.begin([] (void ()) {
    programManager.suspend();
    roboCarHandler.stop();
  }, 10);

  rf24Listener.set(&hangingDetector);
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
