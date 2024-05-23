#ifndef __PS2_CONTROLLER_H__
#define __PS2_CONTROLLER_H__

#include "Pokerobo_PSx.h"
#include "Pokerobo_Car.h"

class PS2InputDispatcher: public PS2Processor, public InputController {
  public:
    virtual uint32_t process(PS2ControlPacket* packet);
  protected:
    bool isDebugEnabled();
    bool isJoystickChanged(int, int);
    int adjustJoystickX(int nJoyX);
    int adjustJoystickY(int nJoyY);
  private:
    bool _debugEnabled;
};

#endif
