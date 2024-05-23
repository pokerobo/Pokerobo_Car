#ifndef __POKEROBO_CAR_INPUT_LISTENER_H__
#define __POKEROBO_CAR_INPUT_LISTENER_H__

#include "Commons.h"
#include "Moving_Command.h"
#include "Pokerobo_RCB_client.h"

class InputListener {
  public:
    virtual int read(MasterContext* context, JoystickAction* action, MovingCommand* command);
};

#endif
