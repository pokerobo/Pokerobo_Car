#include "Motor_Speed_Calculator.h"
#include "TimerOne.h"

MotorRotationCounter* MotorSpeedCalculator::counterForMotorA_ = NULL;
MotorRotationCounter* MotorSpeedCalculator::counterForMotorB_ = NULL;
MotorRotationCounter* MotorSpeedCalculator::counterForMotorC_ = NULL;
MotorRotationCounter* MotorSpeedCalculator::counterForMotorD_ = NULL;

volatile float MotorSpeedCalculator::speedOfMotorA = 0.0;
volatile float MotorSpeedCalculator::speedOfMotorB = 0.0;
volatile float MotorSpeedCalculator::speedOfMotorC = 0.0;
volatile float MotorSpeedCalculator::speedOfMotorD = 0.0;

void MotorSpeedCalculator::start() {
  begin();
}

void MotorSpeedCalculator::begin(byte type,
        byte pinForA,
        byte pinForB,
        byte pinForC,
        byte pinForD) {
  Timer1.initialize(1000000); // set timer for 1sec

  if (type & 0b0001) {
    counterForMotorA_ = new MotorRotationCounter(0,
        digitalPinToInterrupt(pinForA));
  }

  if (type & 0b0010) {
    counterForMotorB_ = new MotorRotationCounter(1,
        digitalPinToInterrupt(pinForB));
  }

  if (type & 0b0100) {
    counterForMotorC_ = new MotorRotationCounter(2,
        digitalPinToInterrupt(pinForC));
  }

  if (type & 0b1000) {
    counterForMotorD_ = new MotorRotationCounter(3,
        digitalPinToInterrupt(pinForD));
  }

  if (counterForMotorA_ != NULL) {
    counterForMotorA_->begin ();
  }
  if (counterForMotorB_ != NULL) {
    counterForMotorB_->begin ();
  }
  if (counterForMotorC_ != NULL) {
    counterForMotorC_->begin ();
  }
  if (counterForMotorD_ != NULL) {
    counterForMotorD_->begin ();
  }

  Timer1.attachInterrupt(isr);
}

void MotorSpeedCalculator::isr () {
  Timer1.detachInterrupt();
  calculate();
  Timer1.attachInterrupt(isr);
}

void MotorSpeedCalculator::calculate () {
  if (counterForMotorA_ != NULL) {
    speedOfMotorA = calculateRPM(counterForMotorA_);
  }
  if (counterForMotorB_ != NULL) {
    speedOfMotorB = calculateRPM(counterForMotorB_);
  }
  if (counterForMotorC_ != NULL) {
    speedOfMotorC = calculateRPM(counterForMotorC_);
  }
  if (counterForMotorD_ != NULL) {
    speedOfMotorD = calculateRPM(counterForMotorD_);
  }
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
