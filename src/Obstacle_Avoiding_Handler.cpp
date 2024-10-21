#include "Obstacle_Avoiding_Handler.h"
#include <Servo.h>

#ifndef RC_DEFAULT_SERVO_PIN
#define RC_DEFAULT_SERVO_PIN          2
#endif

ObstacleAvoidingHandler::ObstacleAvoidingHandler(RoboCarHandler *carHandler,
        UntrasonicReader *sonar, void *servo) {
  _roboCarHandler = carHandler;
  _sonar = sonar;
  _servo = servo != NULL ? servo : new Servo();
}

void ObstacleAvoidingHandler::begin() {
  _distance = 0;
  _prevDistance = 0;
  attachServo(RC_DEFAULT_SERVO_PIN);
  rotateServo(_sonarDefaultPositionAngle);
}

uint32_t ObstacleAvoidingHandler::lookLeft() {
  rotateServo(min(180, _sonarDefaultPositionAngle + _probeRotationAngle));
  delay(500);
  uint32_t distance = _sonar->distance_cm();
  delay(100);
  rotateServo(_sonarDefaultPositionAngle);
  delay(200);
  return distance;
}

void ObstacleAvoidingHandler::attachServo(byte pin) {
  if (_servo == NULL) return;
  Servo* servo_ = (Servo*)_servo;
  if (!servo_->attached()) {
    servo_->attach(pin);
  }
}

void ObstacleAvoidingHandler::rotateServo(byte angle) {
  if (_servo == NULL) return;
  Servo* servo_ = (Servo*)_servo;
  servo_->write(angle);
}

uint32_t ObstacleAvoidingHandler::lookRight() {
  rotateServo(max(0, _sonarDefaultPositionAngle - _probeRotationAngle));
  delay(500);
  uint32_t distance = _sonar->distance_cm();
  delay(100);
  rotateServo(_sonarDefaultPositionAngle);
  delay(200);
  return distance;
}

void ObstacleAvoidingHandler::turnLeft() {
  _roboCarHandler->move(-1, _wheelSpeed, _wheelSpeed, 1);
  delay(_turnLeftDuration);
  _roboCarHandler->move(0, _wheelSpeed, _wheelSpeed, 0);
}

void ObstacleAvoidingHandler::turnRight() {
  _roboCarHandler->move(1, _wheelSpeed, _wheelSpeed, -1);
  delay(_turnRightDuration);
  _roboCarHandler->move(0, _wheelSpeed, _wheelSpeed, 0);
} 

void ObstacleAvoidingHandler::moveForward() {
  _roboCarHandler->move(1, _wheelSpeed, _wheelSpeed, 1);
}

void ObstacleAvoidingHandler::moveBackward() {
  _roboCarHandler->move(-1, _wheelSpeed, _wheelSpeed, -1);
  delay(_movingBackwardDuration);
  _roboCarHandler->move(0, _wheelSpeed, _wheelSpeed, 0);
}

void ObstacleAvoidingHandler::moveStop() {
  _roboCarHandler->move(0, _wheelSpeed, _wheelSpeed, 0);
  delay(100);
}

uint32_t ObstacleAvoidingHandler::detectObstacle() {
  _prevDistance = _distance;
  _distance = _sonar->distance_cm();
  if (_distance == 0) {
    _distance = (_prevDistance > _minDistanceToObstacle) ? 400 : 2;
  }
  return _distance;
}

bool ObstacleAvoidingHandler::willBeCollided() {
  return detectObstacle() < _minDistanceToObstacle;
}

void ObstacleAvoidingHandler::move() {
  if(willBeCollided()) {
    moveStop();
    moveBackward();

    if(lookLeft() > lookRight()) {
      turnLeft();
    } else {
      turnRight();
    }
  } else {
    moveForward();
  }
}

void ObstacleAvoidingHandler::setSonarDefaultPositionAngle(byte angle) {
  if (_sonarDefaultPositionAngle > 180) return;
  _sonarDefaultPositionAngle = angle;
}

void ObstacleAvoidingHandler::setProbeRotationAngle(byte angle) {
  if (_probeRotationAngle > min(_sonarDefaultPositionAngle, 90)) return;
  _probeRotationAngle = angle;
}

void ObstacleAvoidingHandler::setMinDistanceToObstacle(uint16_t distance) {
  if (distance > 400) return;
  _minDistanceToObstacle = distance;
}

void ObstacleAvoidingHandler::setMovingBackwardDuration(uint16_t duration) {
  _movingBackwardDuration = duration;
}

void ObstacleAvoidingHandler::setTurnLeftDuration(uint16_t duration) {
  _turnLeftDuration = duration;
}

void ObstacleAvoidingHandler::setTurnRightDuration(uint16_t duration) {
  _turnRightDuration = duration;
}

void ObstacleAvoidingHandler::setWheelSpeed(byte speed) {
  _wheelSpeed = speed;
}
