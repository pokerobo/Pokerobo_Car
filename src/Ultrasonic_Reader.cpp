#include "Ultrasonic_Reader.h"
#include <NewPing.h>

bool UltrasonicReader::isActive() {
  return _active;
}

//-------------------------------------------------------------------------------------------------

UltrasonicReaderInRawCode::UltrasonicReaderInRawCode(uint8_t trigger_pin,
        uint8_t echo_pin) {
  _triggerPin = trigger_pin;
  _echoPin = echo_pin;
}

void UltrasonicReaderInRawCode::begin() {
  _active = true;
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

unsigned long UltrasonicReaderInRawCode::distance_cm() {
  return estimate() * 0.0343 / 2;
}

unsigned long UltrasonicReaderInRawCode::distance_in() {
  return estimate() * 0.0135 / 2;
}

unsigned long UltrasonicReaderInRawCode::ping() {
  return estimate();
}

unsigned long UltrasonicReaderInRawCode::estimate() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin, LOW);
  return pulseIn(_echoPin, HIGH);
}

//-------------------------------------------------------------------------------------------------

UltrasonicReaderByNewPing::UltrasonicReaderByNewPing(uint8_t trigger_pin,
        uint8_t echo_pin,
        unsigned int max_cm_distance) {
  _sonarRef = new NewPing(trigger_pin, echo_pin, max_cm_distance);
}

UltrasonicReaderByNewPing::~UltrasonicReaderByNewPing() {
  if (_sonarRef == NULL) return;
  NewPing* _sonar = (NewPing*)_sonarRef;
  delete _sonar;
}

void UltrasonicReaderByNewPing::begin() {
  _active = true;
}

unsigned long UltrasonicReaderByNewPing::distance_cm() {
  if (_sonarRef == NULL) return 0;
  NewPing* _sonar = (NewPing*)_sonarRef;
  return _sonar->ping_cm();
}

unsigned long UltrasonicReaderByNewPing::distance_in() {
  if (_sonarRef == NULL) return 0;
  NewPing* _sonar = (NewPing*)_sonarRef;
  return _sonar->ping_in();
}

unsigned long UltrasonicReaderByNewPing::ping() {
  if (_sonarRef == NULL) return 0;
  NewPing* _sonar = (NewPing*)_sonarRef;
  return _sonar->ping();
}
