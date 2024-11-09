#ifndef __POKEROBO_CAR_MOTOR_SPEED_CALCULATOR_H__
#define __POKEROBO_CAR_MOTOR_SPEED_CALCULATOR_H__

#include "Motor_Rotation_Counter.h"

class MotorSpeedCalculator {
  public:
    static volatile float speedOfMotorA;
    static volatile float speedOfMotorB;
    static void start ();
  protected:
    static void isr ();
    static void calculate ();
    static float calculateRPM (MotorRotationCounter* counter);
    static MotorRotationCounter counterForMotorA_;
    static MotorRotationCounter counterForMotorB_;
};

#endif
