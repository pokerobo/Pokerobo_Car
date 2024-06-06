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

int RoboCarHandler::begin() {
  // Set all the motor control pins to outputs
	pinMode(EN_A, OUTPUT);
	pinMode(EN_B, OUTPUT);
	pinMode(IN_1, OUTPUT);
	pinMode(IN_2, OUTPUT);
	pinMode(IN_3, OUTPUT);
	pinMode(IN_4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(IN_1, LOW);
	digitalWrite(IN_2, LOW);
	digitalWrite(IN_3, LOW);
	digitalWrite(IN_4, LOW);
}

void RoboCarHandler::set(MovingResolver* movingResolver) {
  _movingResolver = movingResolver;
}

bool RoboCarHandler::isActive() {
  return _active;
}

void RoboCarHandler::turnOn() {
  _active = true;
  #if __ROBOCAR_RUNNING_LOG__
  debugTurnOn_();
  #endif
}

void RoboCarHandler::turnOff() {
  #if __ROBOCAR_RUNNING_LOG__
  debugTurnOff_();
  #endif
  stop();
  _active = false;
}

void RoboCarHandler::flip() {
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

  if (!_active) {
    x = y = 0;
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
  debugWriteL298nPins_(in1Val, in2Val, in3Val, in4Val, enaVal, enbVal);
  #endif

  digitalWrite(IN_1, in1Val);
  digitalWrite(IN_2, in2Val);
  digitalWrite(IN_3, in3Val);
  digitalWrite(IN_4, in4Val);

  analogWrite(EN_A, enaVal);
  analogWrite(EN_B, enbVal);
}

void RoboCarHandler::stop() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(EN_A, 0);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(EN_B, 0);

  #if __ROBOCAR_RUNNING_LOG__
  debugStop_();
  #endif
}

void RoboCarHandler::debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
    int enaVal, int enbVal) {
}

void RoboCarHandler::debugTurnOn_() {
}

void RoboCarHandler::debugTurnOff_() {
}

void RoboCarHandler::debugStop_() {
}

//-------------------------------------------------------------------------------------------------

void RoboCarHandlerVerbose::debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
    int enaVal, int enbVal) {
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

void RoboCarHandlerVerbose::debugTurnOn_() {
  if (isDebugEnabled()) {
    getLogger()->debug("RoboCarHandler", "::", "turnOn", "()");
  }
}

void RoboCarHandlerVerbose::debugTurnOff_() {
  if (isDebugEnabled()) {
    getLogger()->debug("RoboCarHandler", "::", "turnOff", "()");
  }
}

void RoboCarHandlerVerbose::debugStop_() {
  if (isDebugEnabled()) {
    getLogger()->debug("RoboCarHandler", "::", "stop", "()");
  }
}
