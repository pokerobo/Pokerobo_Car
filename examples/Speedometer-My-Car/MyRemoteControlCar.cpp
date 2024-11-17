#include "MyRemoteControlCar.h"

void MyRemoteControlCar::showSpeedometer_(JoystickAction* action, MovingCommand* command) {
  if (getDisplayAdapter() == NULL) return;
  if (getSpeedometerAdapter() == NULL) {
    getDisplayAdapter()->render(0, 0, _title);
    char text[17] = {};
    sprintf(text, fmt, command->getLeftSpeed(), command->getRightSpeed());
    getDisplayAdapter()->render(0, 1, text);
  } else {
    char text[17] = {};

    sprintf(text, "F: L%4d - R%4d",
        command->getLeftSpeed(),
        command->getRightSpeed());
    getDisplayAdapter()->render(0, 0, text);

    text[0] = 0;
    sprintf(text, "S: %5d - %5d",
        (uint16_t)getSpeedometerAdapter()->getSpeedOfMotorA(),
        (uint16_t)getSpeedometerAdapter()->getSpeedOfMotorB());
    getDisplayAdapter()->render(0, 1, text);
  }
}
