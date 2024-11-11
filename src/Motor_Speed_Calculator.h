#ifndef __POKEROBO_CAR_MOTOR_SPEED_CALCULATOR_H__
#define __POKEROBO_CAR_MOTOR_SPEED_CALCULATOR_H__

#include "Motor_Rotation_Counter.h"

#define POKEROBO_CAR_2WHEELS   0b0011
#define POKEROBO_CAR_4WHEELS   0b1111

#ifndef DIGITAL_PIN_FOR_INTA
#define DIGITAL_PIN_FOR_INTA    2
#endif//DIGITAL_PIN_FOR_INTA

#ifndef DIGITAL_PIN_FOR_INTB
#define DIGITAL_PIN_FOR_INTB    3
#endif//DIGITAL_PIN_FOR_INTB

#ifndef DIGITAL_PIN_FOR_INTC
#define DIGITAL_PIN_FOR_INTC    18
#endif//DIGITAL_PIN_FOR_INTC

#ifndef DIGITAL_PIN_FOR_INTD
#define DIGITAL_PIN_FOR_INTD    19
#endif//DIGITAL_PIN_FOR_INTD


class MotorSpeedCalculator {
  public:
    static volatile float speedOfMotorA;
    static volatile float speedOfMotorB;
    static volatile float speedOfMotorC;
    static volatile float speedOfMotorD;
    static void start ();
    static void begin (byte type = POKEROBO_CAR_2WHEELS,
        byte pinForA = DIGITAL_PIN_FOR_INTA,
        byte pinForB = DIGITAL_PIN_FOR_INTB,
        byte pinForC = DIGITAL_PIN_FOR_INTC,
        byte pinForD = DIGITAL_PIN_FOR_INTD);
  protected:
    static void isr ();
    static void calculate ();
    static float calculateRPM (MotorRotationCounter* counter);
    static MotorRotationCounter* counterForMotorA_;
    static MotorRotationCounter* counterForMotorB_;
    static MotorRotationCounter* counterForMotorC_;
    static MotorRotationCounter* counterForMotorD_;
};

#endif
