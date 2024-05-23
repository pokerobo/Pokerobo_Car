#ifndef __POKEROBO_CAR_ROBOCAR_PROGRAMS_H__
#define __POKEROBO_CAR_ROBOCAR_PROGRAMS_H__

#include "Commons.h"
#include "Display_Adapter.h"
#include "Moving_Command.h"
#include "Line_Detector.h"
#include "RoboCar_Handler.h"
#include "Pokerobo_Arm.h"
#include "Pokerobo_RCB_client.h"

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
        RoboCarHandler* roboCarHandler=NULL);
    void set(DisplayAdapter* displayAdapter);
    void set(RoboCarHandler* roboCarHandler);
  protected:
    virtual void showSpeedometer_(JoystickAction* action, MovingCommand* command);
    DisplayAdapter* getDisplayAdapter();
    RoboCarHandler* getRoboCarHandler();
    bool isDebugEnabled();
  private:
    char* _title;
    DisplayAdapter* _displayAdapter = NULL;
    RoboCarHandler* _roboCarHandler = NULL;
    bool _debugEnabled = true;
};

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

class DancingPuppetCar: public RemoteControlCar {
  public:
    // BEGIN: overriding
    uint8_t getId();
    int begin();
    int check(void* action, void* command);
    int close();
    // END: overriding
    DancingPuppetCar(char* title,
        DisplayAdapter* displayAdapter=NULL,
        RoboCarHandler* roboCarHandler=NULL,
        PedestalGroup* pedestalGroup=NULL,
        bool autoPedestal=false): RemoteControlCar(title,
            displayAdapter,
            roboCarHandler) {
              _pedestalGroup = pedestalGroup;
              _autoPedestal = autoPedestal;
            };
    void set(DisplayAdapter* displayAdapter);
    void set(RoboCarHandler* roboCarHandler);
    void set(PedestalGroup* pedestalGroup, bool autoPedestal=false);
  private:
    PedestalGroup* _pedestalGroup = NULL;
    bool _autoPedestal = false;
};

#endif
