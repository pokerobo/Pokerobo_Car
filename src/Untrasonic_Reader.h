#ifndef __POKEROBO_CAR_UNTRASONIC_READER_H__
#define __POKEROBO_CAR_UNTRASONIC_READER_H__

#include <Arduino.h>

class UntrasonicReader {
  public:
    virtual void begin();
    virtual unsigned long distance_cm();
    virtual unsigned long distance_in();
    virtual unsigned long ping();
};

class UntrasonicReaderInRawCode: public UntrasonicReader {
  public:
    UntrasonicReaderInRawCode(uint8_t trigger_pin = A2,
        uint8_t echo_pin = A3);
    void begin();
    unsigned long distance_cm();
    unsigned long distance_in();
    unsigned long ping();
  protected:
    unsigned long estimate();
  private:
    uint8_t _triggerPin = A2;
    uint8_t _echoPin = A3;
};

class UntrasonicReaderByNewPing: public UntrasonicReader {
  public:
    UntrasonicReaderByNewPing(uint8_t trigger_pin = A2,
        uint8_t echo_pin = A3,
        unsigned int max_cm_distance = 500);
    ~UntrasonicReaderByNewPing();
    void begin();
    unsigned long distance_cm();
    unsigned long distance_in();
    unsigned long ping();
  private:
    void* _sonarRef = NULL;
};

#endif
