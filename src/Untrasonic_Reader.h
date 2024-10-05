#ifndef __POKEROBO_CAR_UNTRASONIC_READER_H__
#define __POKEROBO_CAR_UNTRASONIC_READER_H__

#include <Arduino.h>

class UntrasonicReader {
  public:
    virtual void begin();
    virtual unsigned long ping_cm();
    virtual unsigned long ping_in();
    virtual unsigned long ping();
};

class UntrasonicReaderInRawCode: public UntrasonicReader {
  public:
    UntrasonicReaderInRawCode(uint8_t trigger_pin,
        uint8_t echo_pin);
    void begin();
    unsigned long ping_cm();
    unsigned long ping_in();
    unsigned long ping();
  protected:
    unsigned long estimate();
  private:
    uint8_t _triggerPin = A0;
    uint8_t _echoPin = A1;
};

class UntrasonicReaderByNewPing: public UntrasonicReader {
  public:
    UntrasonicReaderByNewPing(uint8_t trigger_pin,
        uint8_t echo_pin,
        unsigned int max_cm_distance = 500);
    ~UntrasonicReaderByNewPing();
    void begin();
    unsigned long ping_cm();
    unsigned long ping_in();
    unsigned long ping();
  private:
    void* _sonarRef = NULL;
};

#endif
