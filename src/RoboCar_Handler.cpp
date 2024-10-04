#include "RoboCar_Handler.h"

// Motor A connections
#define EN_A    6
#define IN_1    7
#define IN_2    8

// Motor B connections
#define IN_3    5
#define IN_4    4
#define EN_B    3

#define ROBOCAR_DEADZONE_BOUND_X    52
#define ROBOCAR_DEADZONE_BOUND_Y    52

RoboCarHandler::RoboCarHandler(MovingResolver* movingResolver) {
  _movingResolver = movingResolver;
}

void RoboCarHandler::set(MovingResolver* movingResolver) {
  _movingResolver = movingResolver;
}

int RoboCarHandler::begin() {
  // Set all the motor control pins to outputs
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  // Turn off motors - Initial state
  writeL298nPins_(LOW, LOW, LOW, LOW, 0, 0);
}

pokerobo_car_state_t RoboCarHandler::getState() {
  return _state;
}

bool RoboCarHandler::isIdle() {
  return _state == POKEROBO_CAR_IDLE;
}

bool RoboCarHandler::isActive() {
  return _state != POKEROBO_CAR_IDLE;
}

void RoboCarHandler::turnOn() {
  #if __ROBOCAR_RUNNING_LOG__
  pokerobo_car_state_t prevState = _state;
  #endif
  if (_state == POKEROBO_CAR_IDLE) {
    _state = POKEROBO_CAR_ACTIVE;
  }
  #if __ROBOCAR_RUNNING_LOG__
  debugTurnOn_(prevState);
  #endif
}

void RoboCarHandler::turnOff() {
  #if __ROBOCAR_RUNNING_LOG__
  pokerobo_car_state_t prevState = _state;
  #endif
  stop();
  if (_state == POKEROBO_CAR_STOPPED) {
    _state = POKEROBO_CAR_IDLE;
  }
  #if __ROBOCAR_RUNNING_LOG__
  debugTurnOff_(prevState);
  #endif
}

void RoboCarHandler::toggle() {
  if (isActive()) {
    turnOff();
  } else {
    turnOn();
  }
}

void RoboCarHandler::move(int x, int y, bool reversed) {
  if (!_movingResolver) {
    return;
  }

  MovingCommand packet(reversed);
  _movingResolver->resolve(&packet, x, y);
  move(&packet);
}

void RoboCarHandler::move(MovingCommand* packet) {
  if (packet == NULL) {
    return;
  }
  move(packet->getLeftDirection(), packet->getLeftSpeed(), packet->getRightSpeed(), packet->getRightDirection(),
    packet->isReversed());
}

void RoboCarHandler::move(int8_t leftDirection, int leftSpeed, int rightSpeed, int8_t rightDirection,
    bool reversed) {

  if (_state == POKEROBO_CAR_IDLE) {
    writeL298nPins_(LOW, LOW, LOW, LOW, 0, 0);
    return;
  }

  uint8_t in1Val = LOW;
  uint8_t in2Val = LOW;
  uint8_t in3Val = LOW;
  uint8_t in4Val = LOW;

  switch (leftDirection) {
    case 1:
      in1Val = HIGH;
      break;
    case -1:
    case 2:
      in2Val = HIGH;
      break;
  }

  switch (rightDirection) {
    case 1:
      in3Val = HIGH;
      break;
    case -1:
    case 2:
      in4Val = HIGH;
      break;
  }

  int enaVal = leftSpeed;
  int enbVal = rightSpeed;

  if (reversed) {
    in1Val = HIGH - in1Val;
    in2Val = HIGH - in2Val;
    in3Val = HIGH - in3Val;
    in4Val = HIGH - in4Val;
    int tmpVal = enaVal;
    enaVal = enbVal;
    enbVal = tmpVal;
  }

  #if __ROBOCAR_RUNNING_LOG__
  pokerobo_car_state_t prevState = _state;
  #endif

  writeL298nPins_(in1Val, in2Val, in3Val, in4Val, enaVal, enbVal);
  updateState_(in1Val, in2Val, in3Val, in4Val, enaVal, enbVal);

  #if __ROBOCAR_RUNNING_LOG__
  debugWriteL298nPins_(in1Val, in2Val, in3Val, in4Val, enaVal, enbVal, prevState);
  #endif
}

void RoboCarHandler::stop() {
  #if __ROBOCAR_RUNNING_LOG__
  pokerobo_car_state_t prevState = _state;
  #endif
  writeL298nPins_(LOW, LOW, LOW, LOW, 0, 0);
  updateState_(LOW, LOW, LOW, LOW, 0, 0);
  #if __ROBOCAR_RUNNING_LOG__
  debugStop_(prevState);
  #endif
}

void RoboCarHandler::writeL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
    int enaVal, int enbVal) {
  digitalWrite(IN_1, in1Val);
  digitalWrite(IN_2, in2Val);
  digitalWrite(IN_3, in3Val);
  digitalWrite(IN_4, in4Val);

  analogWrite(EN_A, enaVal);
  analogWrite(EN_B, enbVal);
}

void RoboCarHandler::updateState_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
    int enaVal, int enbVal) {
  if (_state != POKEROBO_CAR_IDLE) {
    bool running = false;
    if (in1Val != in2Val && enaVal != 0) {
      running = true;
    }
    if (in3Val != in4Val && enbVal != 0) {
      running = true;
    }
    _state = running ? POKEROBO_CAR_RUNNING : POKEROBO_CAR_STOPPED;
  }
}

void RoboCarHandler::debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
    int enaVal, int enbVal, pokerobo_car_state_t prevState) {
}

void RoboCarHandler::debugTurnOn_(pokerobo_car_state_t prevState) {
}

void RoboCarHandler::debugTurnOff_(pokerobo_car_state_t prevState) {
}

void RoboCarHandler::debugStop_(pokerobo_car_state_t prevState) {
}

//-------------------------------------------------------------------------------------------------

void RoboCarHandlerVerbose::debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
    int enaVal, int enbVal, pokerobo_car_state_t prevState) {
  if (isDebugEnabled()) {
    char num_[7];
    getLogger()->debug(" - ", "active", ": ", isActive() ? "On" : "Off");
    getLogger()->debug(" - ", "IN_1", ": ", itoa(in1Val, num_, 10));
    getLogger()->debug(" - ", "IN_2", ": ", itoa(in2Val, num_, 10));
    getLogger()->debug(" - ", "IN_3", ": ", itoa(in3Val, num_, 10));
    getLogger()->debug(" - ", "IN_4", ": ", itoa(in4Val, num_, 10));

    getLogger()->debug(" - ", "EN_A", ": ", itoa(enaVal, num_, 10));
    getLogger()->debug(" - ", "EN_B", ": ", itoa(enbVal, num_, 10));
  }
}

void RoboCarHandlerVerbose::debugTurnOn_(pokerobo_car_state_t prevState) {
  if (isDebugEnabled()) {
    getLogger()->debug("RoboCarHandler", "::", "turnOn", "()");
  }
}

void RoboCarHandlerVerbose::debugTurnOff_(pokerobo_car_state_t prevState) {
  if (isDebugEnabled()) {
    getLogger()->debug("RoboCarHandler", "::", "turnOff", "()");
  }
}

void RoboCarHandlerVerbose::debugStop_(pokerobo_car_state_t prevState) {
  if (isDebugEnabled()) {
    getLogger()->debug("RoboCarHandler", "::", "stop", "()");
  }
}
