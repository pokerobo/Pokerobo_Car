#ifndef __POKEROBO_CAR_MOVING_COMMAND_H__
#define __POKEROBO_CAR_MOVING_COMMAND_H__

#include "Commons.h"
#include "Pokerobo_RCB_client.h"

class MovingCommand: public MessageInterface {
  public:
    static const uint8_t messageSize;
    MovingCommand(bool reversed);
    MovingCommand(int leftSpeed=0, byte leftDirection=0, int rightSpeed=0, byte rightDirection=0,
        bool reversed=false);
    void update(int leftSpeed, byte leftDirection, int rightSpeed, byte rightDirection);
    int getLeftSpeed();
    byte getLeftDirection();
    int getRightSpeed();
    byte getRightDirection();
    bool isReversed();
    uint8_t length();
    void* deserialize(uint8_t* buf);
  private:
    int _LeftSpeed;
    byte _LeftDirection;
    int _RightSpeed;
    byte _RightDirection;
    bool _reversed = false;
};

#endif
