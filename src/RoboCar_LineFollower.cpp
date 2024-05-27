#include "RoboCar_LineFollower.h"

//-------------------------------------------------------------------------------------------------

uint8_t LineFollowingCar::getId() {
  return 2;
}

int LineFollowingCar::check(void* action_, void* command_) {
  JoystickAction* action = (JoystickAction*) action_;
  MovingCommand* command = (MovingCommand*) command_;

  if (_lineDetector != NULL) {
    uint8_t lineSignals = _lineDetector->read();

    if (isDebugEnabled()) {
      Serial.print("LineSignals: "), Serial.print(lineSignals, BIN), Serial.println();
    }

    // transforms the 10001 -> "-|||-", 1: white(-); 0: black(|)
    char lineText[16] = { 0 };
    for (int i=0; i<5; i++) {
      if ((lineSignals >> i) & 0b1) {
        lineText[i] = '-';
      } else {
        lineText[i] = '|';
      }
    }

    // show the line signals to the screen
    if (getDisplayAdapter() != NULL) {
      getDisplayAdapter()->render(5, 0, lineText);
    }
  }

  return RemoteControlCar::check(action_, command_);
}

void LineFollowingCar::set(DisplayAdapter* displayAdapter) {
  RemoteControlCar::set(displayAdapter);
}

void LineFollowingCar::set(RoboCarHandler* roboCarHandler) {
  RemoteControlCar::set(roboCarHandler);
}

void LineFollowingCar::set(LineDetector* lineDetector) {
  _lineDetector = lineDetector;
}

void LineFollowingCar::showSpeedometer_(JoystickAction* action, MovingCommand* command) {
  if (getDisplayAdapter() != NULL) {
    char text[16] = {};
    sprintf(text, fmt, command->getLeftSpeed(), command->getRightSpeed());
    getDisplayAdapter()->render(0, 1, text);
  }
}
