#ifndef __POKEROBO_CAR_MOTOR_ROTATION_COUNTER_H__
#define __POKEROBO_CAR_MOTOR_ROTATION_COUNTER_H__

#include <Arduino.h>

class MotorRotationCounter {
  static void isr0 ();
  static void isr1 ();
  static void isr2 ();
  static void isr3 ();

  const byte whichISR_;
  const byte interruptNumber_;
  const float diskslots_;

  static MotorRotationCounter * instance0_;
  static MotorRotationCounter * instance1_;
  static MotorRotationCounter * instance2_;
  static MotorRotationCounter * instance3_;

  void handleInterrupt ();

  volatile uint16_t counter_;

  public:
    MotorRotationCounter (const byte which, const byte intnum,
        const byte diskslots = 20);
    void begin ();
    float getNumOfDiskSlots ();
    float getNumOfRevolutions ();
    uint16_t getCounter (bool reset = false);
    void resetCounter ();
};

#endif
