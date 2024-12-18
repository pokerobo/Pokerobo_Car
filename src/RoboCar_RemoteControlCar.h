#ifndef __POKEROBO_CAR_ROBOCAR_REMOTE_CONTROL_H__
#define __POKEROBO_CAR_ROBOCAR_REMOTE_CONTROL_H__

#include "Commons.h"
#include "Display_Adapter.h"
#include "Moving_Command.h"
#include "RoboCar_Handler.h"
#include "Speedometer_Adapter.h"
#include "Pokerobo_RCB_client.h"

const char fmt[] = "L:%4d - R:%4d";

class RemoteControlCar: public ProgramCapsule {
  public:
    // BEGIN: overriding
    uint8_t getId();
    virtual char* getTitle();
    virtual int begin();
    virtual int check(void* action, void* command);
    virtual int close();
    // END: overriding
    RemoteControlCar(char* title,
        DisplayAdapter* displayAdapter=NULL,
        RoboCarHandler* roboCarHandler=NULL,
        SpeedometerAdapter* speedometerAdapter=NULL);
    void set(DisplayAdapter* displayAdapter);
    void set(RoboCarHandler* roboCarHandler);
  protected:
    virtual void showSpeedometer_(JoystickAction* action, MovingCommand* command);
    DisplayAdapter* getDisplayAdapter();
    RoboCarHandler* getRoboCarHandler();
    SpeedometerAdapter* getSpeedometerAdapter();
    bool isDebugEnabled();
  private:
    char* _title;
    DisplayAdapter* _displayAdapter = NULL;
    RoboCarHandler* _roboCarHandler = NULL;
    SpeedometerAdapter* _speedometerAdapter = NULL;
    bool _debugEnabled = true;
};

#endif
