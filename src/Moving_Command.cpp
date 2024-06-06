#include "Moving_Command.h"

const uint8_t MovingCommand::messageSize = sizeof(uint8_t) +
    sizeof(uint8_t) +
    sizeof(uint8_t);

MovingCommand::MovingCommand(bool reversed) {
  _reversed = reversed;
}

MovingCommand::MovingCommand(int leftSpeed, byte leftDirection, int rightSpeed, byte rightDirection,
    bool reversed) {
  _reversed = reversed;
  update(leftSpeed, leftDirection, rightSpeed, rightDirection);
}

void MovingCommand::update(int leftSpeed, byte leftDirection, int rightSpeed, byte rightDirection) {
  _LeftSpeed = leftSpeed;
  _LeftDirection = leftDirection;
  _RightSpeed = rightSpeed;
  _RightDirection = rightDirection;
}

int MovingCommand::getLeftSpeed() {
  return _LeftSpeed;
}

byte MovingCommand::getLeftDirection() {
  return _LeftDirection;
}

int MovingCommand::getRightSpeed() {
  return _RightSpeed;
}

byte MovingCommand::getRightDirection() {
  return _RightDirection;
}

bool MovingCommand::isReversed() {
  return _reversed;
}

uint8_t MovingCommand::length() {
  return messageSize;
}

void* MovingCommand::deserialize(uint8_t* buf) {
  if (buf == NULL) {
    return NULL;
  }

  uint8_t directionFlags = buf[0];
  _LeftDirection = directionFlags & 0b0011;
  _RightDirection = (directionFlags & 0b1100) >> 2;
  _reversed = (directionFlags & 0b10000000) != 0;
  _LeftSpeed = buf[1];
  _RightSpeed = buf[2];

  return this;
}
