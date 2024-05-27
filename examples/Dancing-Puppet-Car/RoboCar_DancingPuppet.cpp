#include "RoboCar_DancingPuppet.h"

//-------------------------------------------------------------------------------------------------

uint8_t DancingPuppetCar::getId() {
  return 3;
}

int DancingPuppetCar::begin() {
  return RemoteControlCar::begin();
}

int DancingPuppetCar::check(void* action_, void* command_) {
  JoystickAction* action = (JoystickAction*) action_;
  MovingCommand* command = (MovingCommand*) command_;

  if (_autoPedestal) {
    if (_pedestalGroup != NULL) {
      _pedestalGroup->autoDance();
    }
  }

  return RemoteControlCar::check(action_, command_);
}

int DancingPuppetCar::close() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->reset();
  }

  return RemoteControlCar::close();
}

void DancingPuppetCar::set(DisplayAdapter* displayAdapter) {
  RemoteControlCar::set(displayAdapter);
}

void DancingPuppetCar::set(RoboCarHandler* roboCarHandler) {
  RemoteControlCar::set(roboCarHandler);
}

void DancingPuppetCar::set(PedestalGroup* pedestalGroup, bool autoPedestal) {
  _pedestalGroup = pedestalGroup;
  _autoPedestal = autoPedestal;
}
