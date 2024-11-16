#ifndef __POKEROBO_CAR_SPEEDOMETER_WRAPPER_H__
#define __POKEROBO_CAR_SPEEDOMETER_WRAPPER_H__

#include "Speedometer_Adapter.h"

class SpeedometerWrapper: public SpeedometerAdapter {
  public:
    void begin();
    float getSpeedOfMotorA();
    float getSpeedOfMotorB();
};

#endif
