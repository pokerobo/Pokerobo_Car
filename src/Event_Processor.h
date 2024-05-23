#ifndef __POKEROBO_CAR_EVENT_PROCESSOR_H__
#define __POKEROBO_CAR_EVENT_PROCESSOR_H__

#include "Commons.h"
#include "Moving_Command.h"
#include "Pokerobo_RCB_client.h"

class EventProcessor {
  public:
    virtual void processEvents(JoystickAction* action, MovingCommand* command);
};

#endif
