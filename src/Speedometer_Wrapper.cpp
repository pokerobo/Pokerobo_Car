#include "Speedometer_Wrapper.h"
#include "Motor_Speed_Calculator.h"

void SpeedometerWrapper::begin() {
  MotorSpeedCalculator::begin();
}

float SpeedometerWrapper::getSpeedOfMotorA() {
  return MotorSpeedCalculator::speedOfMotorA;
}

float SpeedometerWrapper::getSpeedOfMotorB() {
  return MotorSpeedCalculator::speedOfMotorB;
}
