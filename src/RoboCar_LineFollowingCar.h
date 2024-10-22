#ifndef __POKEROBO_CAR_ROBOCAR_LINE_FOLLOWER_H__
#define __POKEROBO_CAR_ROBOCAR_LINE_FOLLOWER_H__

#include "Line_Detector.h"
#include "Pokerobo_Arm.h"
#include "RoboCar_RemoteControlCar.h"

class LineFollowingCar: public RemoteControlCar {
  public:
    // BEGIN: overriding
    uint8_t getId();
    int check(void* action, void* command);
    // END: overriding
    LineFollowingCar(char* title,
        DisplayAdapter* displayAdapter=NULL,
        RoboCarHandler* roboCarHandler=NULL): RemoteControlCar(title,
            displayAdapter,
            roboCarHandler) {};
    void set(DisplayAdapter* displayAdapter);
    void set(RoboCarHandler* roboCarHandler);
    void set(LineDetector* lineDetector);
  protected:
    void showSpeedometer_(JoystickAction* action, MovingCommand* command);
  private:
    LineDetector* _lineDetector = NULL;
};

#endif
