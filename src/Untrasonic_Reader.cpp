#include "Untrasonic_Reader.h"
#include <NewPing.h>

UntrasonicReaderInRawCode::UntrasonicReaderInRawCode(uint8_t trigger_pin,
        uint8_t echo_pin) {
  _triggerPin = trigger_pin;
  _echoPin = echo_pin;
}

void UntrasonicReaderInRawCode::begin() {
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

unsigned long UntrasonicReaderInRawCode::distance_cm() {
  return estimate() * 0.0343 / 2;
}

unsigned long UntrasonicReaderInRawCode::distance_in() {
  return estimate() * 0.0135 / 2;
}

unsigned long UntrasonicReaderInRawCode::ping() {
  return estimate();
}

unsigned long UntrasonicReaderInRawCode::estimate() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin, LOW);
  return pulseIn(_echoPin, HIGH);
}

UntrasonicReaderByNewPing::UntrasonicReaderByNewPing(uint8_t trigger_pin,
        uint8_t echo_pin,
        unsigned int max_cm_distance) {
  _sonarRef = new NewPing(trigger_pin, echo_pin, max_cm_distance);
}

UntrasonicReaderByNewPing::~UntrasonicReaderByNewPing() {
  if (_sonarRef == NULL) return;
  NewPing* _sonar = (NewPing*)_sonarRef;
  delete _sonar;
}

void UntrasonicReaderByNewPing::begin() {
}

unsigned long UntrasonicReaderByNewPing::distance_cm() {
  if (_sonarRef == NULL) return 0;
  NewPing* _sonar = (NewPing*)_sonarRef;
  return _sonar->ping_cm();
}

unsigned long UntrasonicReaderByNewPing::distance_in() {
  if (_sonarRef == NULL) return 0;
  NewPing* _sonar = (NewPing*)_sonarRef;
  return _sonar->ping_in();
}

unsigned long UntrasonicReaderByNewPing::ping() {
  if (_sonarRef == NULL) return 0;
  NewPing* _sonar = (NewPing*)_sonarRef;
  return _sonar->ping();
}
