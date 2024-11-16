#ifndef __POKEROBO_CAR_SPEEDOMETER_ADAPTER_H__
#define __POKEROBO_CAR_SPEEDOMETER_ADAPTER_H__

class SpeedometerAdapter {
  public:
    virtual void begin();
    virtual float getSpeedOfMotorA();
    virtual float getSpeedOfMotorB();
};

#endif
