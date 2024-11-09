#include "Motor_Speed_Calculator.h"
#include "TimerOne.h"

MotorRotationCounter MotorSpeedCalculator::counterForMotorA_ (0);
MotorRotationCounter MotorSpeedCalculator::counterForMotorB_ (1);

volatile float MotorSpeedCalculator::speedOfMotorA = 0.0;
volatile float MotorSpeedCalculator::speedOfMotorB = 0.0;

void MotorSpeedCalculator::start() {
  Timer1.initialize(1000000); // set timer for 1sec

  counterForMotorA_.begin ();
  counterForMotorB_.begin ();

  Timer1.attachInterrupt(isr);
}

void MotorSpeedCalculator::isr () {
  Timer1.detachInterrupt();
  calculate();
  Timer1.attachInterrupt(isr);
}

void MotorSpeedCalculator::calculate () {
  speedOfMotorA = calculateRPM(&counterForMotorA_);
  speedOfMotorB = calculateRPM(&counterForMotorB_);
  #if WHEEL_MOTOR_SPEED_CALIBRATOR_DEBUG_ENABLED
  Serial.print("Speed of Motor A: ");
  Serial.print(speedOfMotorA);
  Serial.print(" RPM");

  Serial.print(" - ");

  Serial.print("Speed of Motor B: ");
  Serial.print(speedOfMotorB);
  Serial.println(" RPM");
  #endif
}

float MotorSpeedCalculator::calculateRPM (MotorRotationCounter* mrc) {
  return (mrc->getCounter(true) / mrc->getNumOfDiskSlots()) * 60.00;
}
