#ifndef __ROBOCAR_PROGRAMS_H__
#define __ROBOCAR_PROGRAMS_H__

#include "Commons.h"
#include "Program_Capsule.h"
#include "Joystick_Action.h"
#include "Moving_Command.h"

#include "Pedestal_Group.h"
#include "RoboCar_Handler.h"

class RemoteControlCar: public ProgramCapsule {
  public:
    RemoteControlCar(char* title,
    RoboCarHandler* roboCarHandler=NULL,
    PedestalGroup* pedestalGroup=NULL,
    bool autoPedestal=false);
    void set(PedestalGroup* pedestalGroup, bool autoPedestal=false);
    void set(RoboCarHandler* roboCarHandler);
    char* getTitle();
    int begin();
    int check(void* action, void* command);
    int close();
  private:
    char* _title;
    bool _autoPedestal = false;
    PedestalGroup* _pedestalGroup = NULL;
    RoboCarHandler* _roboCarHandler = NULL;
    bool _debugEnabled = true;
};

class LineFollowingCar: ProgramCapsule {
  public:
    LineFollowingCar(char* title);
    char* getTitle();
    int begin();
    int check(void* action, void* command);
    int close();
  private:
    char* _title;
};

#endif