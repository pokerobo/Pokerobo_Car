#include "Motor_Rotation_Counter.h"

MotorRotationCounter::MotorRotationCounter (const byte whichISR,
    const byte intnum, const byte diskslots):
      whichISR_ (whichISR),
      interruptNumber_ (intnum),
      diskslots_ (diskslots) {
  counter_ = 0;
}

void MotorRotationCounter::begin () {
  switch (whichISR_) {
    case 0:
      attachInterrupt (interruptNumber_, isr0, RISING);
      instance0_ = this;
      break;
    case 1:
      attachInterrupt (interruptNumber_, isr1, RISING);
      instance1_ = this;
      break;
    case 2:
      attachInterrupt (interruptNumber_, isr2, RISING);
      instance2_ = this;
      break;
    case 3:
      attachInterrupt (interruptNumber_, isr3, RISING);
      instance3_ = this;
      break;
  } 
}

void MotorRotationCounter::isr0 () {
  instance0_->handleInterrupt ();  
}

void MotorRotationCounter::isr1 () {
  instance1_->handleInterrupt ();  
}

void MotorRotationCounter::isr2 () {
  instance1_->handleInterrupt ();  
}

void MotorRotationCounter::isr3 () {
  instance1_->handleInterrupt ();  
}

void MotorRotationCounter::handleInterrupt () {
  counter_++;
}

float MotorRotationCounter::getNumOfDiskSlots () {
  return diskslots_;
}

float MotorRotationCounter::getNumOfRevolutions () {
  return counter_ / diskslots_;
}

uint16_t MotorRotationCounter::getCounter (bool reset) {
  if (reset) {
    uint16_t r = counter_;
    counter_ = 0;
    return r;
  }
  return counter_;
}

void MotorRotationCounter::resetCounter () {
  counter_ = 0;
}

MotorRotationCounter * MotorRotationCounter::instance0_;
MotorRotationCounter * MotorRotationCounter::instance1_;
MotorRotationCounter * MotorRotationCounter::instance2_;
MotorRotationCounter * MotorRotationCounter::instance3_;
