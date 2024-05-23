#include "PS2_Controller.h"

void PS2Controller::set(EventDispatcher* eventDispatcher) {
  _eventDispatcher = eventDispatcher;
};

int PS2Controller::check() {
  byte vibrate = 0;
  ps2x.read_gamepad(false, vibrate); // disable vibration of the controller
  //
  uint16_t startButtonPressed = processStartButtonPress();
  if (startButtonPressed) {
    return startButtonPressed;
  }
  //
  uint16_t selectButtonPressed = processSelectButtonPress();
  if (selectButtonPressed) {
    return selectButtonPressed;
  }
  //
  // Perform movements based on D-pad buttons
  //
  uint16_t buttonPressed = 0;
  buttonPressed |= processDPadUpButtonPress();
  buttonPressed |= processDPadRightButtonPress();
  buttonPressed |= processDPadDownButtonPress();
  buttonPressed |= processDPadLeftButtonPress();

  //
  if (buttonPressed > 0) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      Serial.print("buttonPressed"), Serial.print(": "), Serial.println(buttonPressed, HEX);
    }
    #endif
    return buttonPressed;
  }
  //
  int lstatus = processJoystickChange(ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY), 'L');
  //
  int rstatus = processJoystickChange(ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY), 'R');
};

int PS2Controller::processStartButtonPress() {
  if (!_onStartButtonPressed && !_eventDispatcher) {
    return 0;
  }
  if(ps2x.Button(PSB_START)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "START", " is pushed");
    }
    #endif
    if (_onStartButtonPressed) {
      _onStartButtonPressed();
    } else {
      _eventDispatcher->processStartButtonPressedEvent();
    }
    return PSB_START;
  }
  return 0;
}

int PS2Controller::processSelectButtonPress() {
  if (!_onSelectButtonPressed && !_eventDispatcher) {
    return 0;
  }
  if(ps2x.Button(PSB_SELECT)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "SELECT", " is pushed");
    }
    #endif
    if (_onSelectButtonPressed) {
      _onSelectButtonPressed();
    } else {
      _eventDispatcher->processSelectButtonPressedEvent();
    }
    return PSB_SELECT;
  }
  return 0;
}

int PS2Controller::processDPadUpButtonPress() {
  if (!_onDPadUpButtonPressed && !_eventDispatcher) {
    return 0;
  }
  if(ps2x.Button(PSB_PAD_UP)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "UP", " is pushed");
    }
    #endif
    if (_onDPadUpButtonPressed) {
      _onDPadUpButtonPressed();
    } else {
      _eventDispatcher->processDPadUpButtonPressedEvent();
    }
    return PSB_PAD_UP;
  }
  return 0;
}

int PS2Controller::processDPadRightButtonPress() {
  if (!_onDPadRightButtonPressed && !_eventDispatcher) {
    return 0;
  }
  if(ps2x.Button(PSB_PAD_RIGHT)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "RIGHT", " is pushed");
    }
    #endif
    if (_onDPadRightButtonPressed) {
      _onDPadRightButtonPressed();
    } else {
      _eventDispatcher->processDPadRightButtonPressedEvent();
    }
    return PSB_PAD_RIGHT;
  }
  return 0;
}

int PS2Controller::processDPadDownButtonPress() {
  if (!_onDPadDownButtonPressed && !_eventDispatcher) {
    return 0;
  }
  if(ps2x.Button(PSB_PAD_DOWN)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "DOWN", " is pushed");
    }
    #endif
    if (_onDPadDownButtonPressed) {
      _onDPadDownButtonPressed();
    } else {
      _eventDispatcher->processDPadDownButtonPressedEvent();
    }
    return PSB_PAD_DOWN;
  }
  return 0;
}

int PS2Controller::processDPadLeftButtonPress() {
  if (!_onDPadLeftButtonPressed) {
    return 0;
  }
  if(ps2x.Button(PSB_PAD_LEFT)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "LEFT", " is pushed");
    }
    #endif
    if (_onDPadLeftButtonPressed) {
      _onDPadLeftButtonPressed();
    } else {
      _eventDispatcher->processDPadLeftButtonPressedEvent();
    }
    return PSB_PAD_LEFT;
  }
  return 0;
}

bool PS2Controller::isDebugEnabled() {
  return PS2Controller_::isDebugEnabled();
}

bool PS2Controller::isJoystickChanged(int nJoyX, int nJoyY) {
  #if defined(PS2_JOYSTICK_CHECKING_CHANGE)
  return nJoyX >= PS2_JOYSTICK_DEADZONE_X || nJoyX <= -PS2_JOYSTICK_DEADZONE_X ||
      nJoyY >= PS2_JOYSTICK_DEADZONE_Y || nJoyY <= -PS2_JOYSTICK_DEADZONE_Y;
  #else
  return true;
  #endif
}

int PS2Controller::adjustJoystickX(int nJoyX) {
  return map(nJoyX, 0, 255, PS2_JOYSTICK_RANGE_X, -PS2_JOYSTICK_RANGE_X);
}

int PS2Controller::adjustJoystickY(int nJoyY) {
  return map(nJoyY, 0, 255, PS2_JOYSTICK_RANGE_Y, -PS2_JOYSTICK_RANGE_Y);
}
