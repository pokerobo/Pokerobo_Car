#ifndef __POKEROBO_CAR_QUICK_START_H__
#define __POKEROBO_CAR_QUICK_START_H__

#include "Pokerobo_Car.h"

DisplayAdapter displayAdapter;

const uint64_t baseAddress = 0x18580900LL;
RF24Listener rf24Listener(baseAddress + 1);
HangingDetector hangingDetector;

MovingResolver movingResolver;
RoboCarHandler roboCarHandler(&movingResolver);

RemoteControlCar remoteControlCar("Quick Start Car",
    &displayAdapter, &roboCarHandler);

ProgramManager programManager(&rf24Listener,
    &displayAdapter, &hangingDetector);

class QuickStartLauncher {
  public:
    void begin(uint8_t address=1);
    void check();
};

void QuickStartLauncher::begin(uint8_t address) {
    displayAdapter.begin();

  roboCarHandler.begin();

  hangingDetector.begin([] (void ()) {
    programManager.suspend();
    roboCarHandler.stop();
  }, 10);

  rf24Listener.set(&hangingDetector);
  rf24Listener.begin(baseAddress + address);

  remoteControlCar.begin();
  programManager.add(&remoteControlCar);
  programManager.begin();
}

void QuickStartLauncher::check() {
  programManager.check();
}

#endif
