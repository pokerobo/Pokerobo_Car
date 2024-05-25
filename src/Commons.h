#ifndef __POKEROBO_CAR_COMMONS_H__
#define __POKEROBO_CAR_COMMONS_H__

#include <Arduino.h>

#define __LOADING_LOG_ENABLED__         1
#define __RUNNING_LOG_ENABLED__         1

#define __RF24_RUNNING_LOG__            0
#define __DISPATCHER_RUNNING_LOG__      0
#define __ROBOCAR_RUNNING_LOG__         1
#define __PEDESTAL_RUNNING_LOG__        0
#define __INPUT_RUNNING_LOG__           1

#define  __DEBUG_LOG_RF24_LISTENER__    0

#define CONTROLLER_PEDESTAL             1
#define CONTROLLER_ROBOCAR              1

#define CONTROLLER_PS2                  2
#define CONTROLLER_RF24                 24
#define CONTROLLER                      CONTROLLER_RF24

#ifndef int_abs
#define int_abs(x) ((x)>0?(x):-(x))
#endif

#ifndef int_min
#define int_min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef int_max
#define int_max(a,b) ((a)>(b)?(a):(b))
#endif

class FlagChecker {
  public:
    FlagChecker();
    bool isAvailable();
  private:
    bool enabled;
    uint32_t limit;
};

class HangingDetector {
  public:
    HangingDetector(void (*trigger)() = NULL, uint16_t limit = 10);
    void begin(void (*trigger)() = NULL, uint16_t limit = 10);
    bool check(bool ok);
    void reset();
  private:
    uint16_t _count = 0;
    uint16_t _limit = 10;
    bool _triggered = false;
    void (*_trigger)();
};

class CarDebugLogger {
  public:
    static void debug(char* s0,
        char* s1=NULL,
        char* s2=NULL,
        char* s3=NULL,
        char* s4=NULL,
        char* s5=NULL,
        char* s6=NULL,
        char* s7=NULL,
        char* s8=NULL,
        char* s9=NULL,
        char* s10=NULL,
        char* s11=NULL,
        char* s12=NULL,
        char* s13=NULL,
        char* s14=NULL,
        char* s15=NULL,
        char* s16=NULL,
        char* s17=NULL,
        char* s18=NULL,
        char* s19=NULL);
};

class CarDebugLoggable {
  public:
    void setDebugEnabled(bool enabled);
    void setDebugLogger(CarDebugLogger* logger);
  protected:
    virtual bool isDebugEnabled();
    virtual CarDebugLogger* getLogger();
  private:
    bool _debugEnabled = true;
    CarDebugLogger* _logger = NULL;
};

#endif
