#include "PS2_Controller.h"

uint32_t PS2InputDispatcher::process(PS2ControlPacket* packet) {
  uint16_t pressed = processButtonPress(packet->getPressingFlags());
  if (pressed) {
    return pressed;
  }
  return processJoystickChange(packet->getX(), packet->getY(), 'L');
}

bool PS2InputDispatcher::isDebugEnabled() {
  return _debugEnabled;
}

bool PS2InputDispatcher::isJoystickChanged(int nJoyX, int nJoyY) {
  #if defined(PS2_JOYSTICK_CHECKING_CHANGE)
  return nJoyX >= PS2_JOYSTICK_DEADZONE_X || nJoyX <= -PS2_JOYSTICK_DEADZONE_X ||
      nJoyY >= PS2_JOYSTICK_DEADZONE_Y || nJoyY <= -PS2_JOYSTICK_DEADZONE_Y;
  #else
  return true;
  #endif
}

int PS2InputDispatcher::adjustJoystickX(int nJoyX) {
  return map(nJoyX, 0, 1024, PS2_JOYSTICK_RANGE_X, -PS2_JOYSTICK_RANGE_X);
}

int PS2InputDispatcher::adjustJoystickY(int nJoyY) {
  return map(nJoyY, 0, 1024, PS2_JOYSTICK_RANGE_Y, -PS2_JOYSTICK_RANGE_Y);
}
