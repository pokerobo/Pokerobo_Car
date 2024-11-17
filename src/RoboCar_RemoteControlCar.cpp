#include "RoboCar_RemoteControlCar.h"

uint8_t RemoteControlCar::getId() {
  return 1;
}

char* RemoteControlCar::getTitle() {
  return _title;
}

int RemoteControlCar::begin() {
  if (_roboCarHandler != NULL) {
    _roboCarHandler->turnOn();
  }
  return 0;
}

int RemoteControlCar::check(void* action_, void* command_) {
  JoystickAction* action = (JoystickAction*) action_;
  MovingCommand* command = (MovingCommand*) command_;

  if (_roboCarHandler) {
    _roboCarHandler->move(command);
  }

  showSpeedometer_(action, command);

  return 0;
}

int RemoteControlCar::close() {
  if (_roboCarHandler != NULL) {
    _roboCarHandler->turnOff();
  }

  return 0;
}

RemoteControlCar::RemoteControlCar(char* title,
    DisplayAdapter* displayAdapter,
    RoboCarHandler* roboCarHandler,
    SpeedometerAdapter* speedometerAdapter) {
  _title = title;
  _displayAdapter = displayAdapter;
  _roboCarHandler = roboCarHandler;
  _speedometerAdapter = speedometerAdapter;
}

void RemoteControlCar::set(DisplayAdapter* displayAdapter) {
  _displayAdapter = displayAdapter;
}

void RemoteControlCar::set(RoboCarHandler* roboCarHandler) {
  _roboCarHandler = roboCarHandler;
}

bool RemoteControlCar::isDebugEnabled() {
  return _debugEnabled;
}

void RemoteControlCar::showSpeedometer_(JoystickAction* action, MovingCommand* command) {
  if (_displayAdapter == NULL) return;
  if (_speedometerAdapter == NULL) {
    _displayAdapter->render(0, 0, _title);
    char text[17] = {};
    sprintf(text, fmt, command->getLeftSpeed(), command->getRightSpeed());
    _displayAdapter->render(0, 1, text);
  } else {
    char text[17] = {};

    sprintf(text, "F: L%4d - R%4d",
        command->getLeftSpeed(),
        command->getRightSpeed());
    _displayAdapter->render(0, 0, text);

    text[0] = 0;
    sprintf(text, "S: L%4d - R%4d",
        (uint16_t)_speedometerAdapter->getSpeedOfMotorA(),
        (uint16_t)_speedometerAdapter->getSpeedOfMotorB());
    _displayAdapter->render(0, 1, text);
  }
}

DisplayAdapter* RemoteControlCar::getDisplayAdapter() {
  return _displayAdapter;
}

RoboCarHandler* RemoteControlCar::getRoboCarHandler() {
  return _roboCarHandler;
}

SpeedometerAdapter* RemoteControlCar::getSpeedometerAdapter() {
  return _speedometerAdapter;
}
