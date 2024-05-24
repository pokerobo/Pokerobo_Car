#ifndef __PS2_CONTROLLER_H__
#define __PS2_CONTROLLER_H__

#include "Pokerobo_PSx.h"
#include "Pokerobo_Car.h"

class PS2Controller: public PS2Controller_, public CarDebugLoggable, public InputController {
  public:
    PS2Controller(): PS2Controller_() {};
    void set(EventDispatcher* eventDispatcher);
    int check();
  protected:
    bool isDebugEnabled();
    CarDebugLogger* getLogger();
    bool isJoystickChanged(int, int);
    int adjustJoystickX(int nJoyX);
    int adjustJoystickY(int nJoyY);
  private:
    EventDispatcher* _eventDispatcher = NULL;
    int processStartButtonPress();
    int processSelectButtonPress();
    int processDPadUpButtonPress();
    int processDPadRightButtonPress();
    int processDPadDownButtonPress();
    int processDPadLeftButtonPress();
};

#endif
