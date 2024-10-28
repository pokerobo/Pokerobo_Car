#ifndef __POKEROBO_CAR_UNTRASONIC_READER_H__
#define __POKEROBO_CAR_UNTRASONIC_READER_H__

#include <Arduino.h>
#include "Constant.h"

#if POKEROBO_CAR_DYNAMIC_CONSTANT_ENABLED
#define __ULTRASONIC_TRIGGER_PIN__  ConstantOfCar::me->pinOfTrigger
#define __ULTRASONIC_ECHO_PIN__     ConstantOfCar::me->pinOfEcho

#else//POKEROBO_CAR_DYNAMIC_CONSTANT_ENABLED
#ifndef __ULTRASONIC_TRIGGER_PIN__
#define __ULTRASONIC_TRIGGER_PIN__  A2
#endif

#ifndef __ULTRASONIC_ECHO_PIN__
#define __ULTRASONIC_ECHO_PIN__     A3
#endif
#endif//POKEROBO_CAR_DYNAMIC_CONSTANT_ENABLED

class UltrasonicReader {
  public:
    virtual void begin();
    virtual unsigned long distance_cm();
    virtual unsigned long distance_in();
    virtual unsigned long ping();
    virtual bool isActive();
  protected:
    bool _active = false;
};

class UltrasonicReaderInRawCode: public UltrasonicReader {
  public:
    UltrasonicReaderInRawCode(uint8_t trigger_pin = __ULTRASONIC_TRIGGER_PIN__,
        uint8_t echo_pin = __ULTRASONIC_ECHO_PIN__);
    void begin();
    unsigned long distance_cm();
    unsigned long distance_in();
    unsigned long ping();
  protected:
    unsigned long estimate();
  private:
    uint8_t _triggerPin = __ULTRASONIC_TRIGGER_PIN__;
    uint8_t _echoPin = __ULTRASONIC_ECHO_PIN__;
};

class UltrasonicReaderByNewPing: public UltrasonicReader {
  public:
    UltrasonicReaderByNewPing(uint8_t trigger_pin = __ULTRASONIC_TRIGGER_PIN__,
        uint8_t echo_pin = __ULTRASONIC_ECHO_PIN__,
        unsigned int max_cm_distance = 500);
    ~UltrasonicReaderByNewPing();
    void begin();
    unsigned long distance_cm();
    unsigned long distance_in();
    unsigned long ping();
  private:
    void* _sonarRef = NULL;
};

#endif
