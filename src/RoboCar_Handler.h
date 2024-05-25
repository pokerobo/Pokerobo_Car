#ifndef __POKEROBO_CAR_ROBOCAR_2WHEELS_H__
#define __POKEROBO_CAR_ROBOCAR_2WHEELS_H__

#ifndef __ROBOCAR_LOADING_LOG__
#define __ROBOCAR_LOADING_LOG__  __LOADING_LOG_ENABLED__
#endif//__ROBOCAR_LOADING_LOG__

#ifndef __ROBOCAR_RUNNING_LOG__
#define __ROBOCAR_RUNNING_LOG__  __RUNNING_LOG_ENABLED__
#endif//__ROBOCAR_RUNNING_LOG__

#define DEFAULT_SPEED 128
#define DEFAULT_COEFF 5

#include "Commons.h"
#include "Moving_Resolver.h"
#include "Moving_Command.h"

class RoboCarHandler: public CarDebugLoggable {
  public:
    int begin();
    bool isActive();
    void turnOn();
    void turnOff();
    void flip();
    void stop();
    void set(MovingResolver* movingResolver);
    void move(int x, int y);
    void move(int8_t leftDirection, int leftSpeed, int rightSpeed, int8_t rightDirection);
    void move(MovingCommand* packet);
  private:
    bool _active = false;
    MovingResolver* _movingResolver = NULL;
};

#endif
