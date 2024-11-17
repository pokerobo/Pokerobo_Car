#ifndef __POKEROBO_CAR_MY_SPEEDOMETER_RC_CAR_H__
#define __POKEROBO_CAR_MY_SPEEDOMETER_RC_CAR_H__

#include "Pokerobo_Car_speedometer.h"

class MyRemoteControlCar: public RemoteControlCar {
  public:
    using RemoteControlCar::RemoteControlCar;
  protected:
    void showSpeedometer_(JoystickAction* action, MovingCommand* command);
};

#endif
