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
    RoboCarHandler(MovingResolver* movingResolver=NULL);
    void set(MovingResolver* movingResolver);
    int begin();
    bool isActive();
    void turnOn();
    void turnOff();
    void flip();
    void stop();
    void move(int x, int y, bool reversed = false);
    void move(int8_t leftDirection, int leftSpeed, int rightSpeed, int8_t rightDirection, bool reversed = false);
    void move(MovingCommand* packet);
  protected:
    void writeL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal);
    virtual void debugTurnOn_();
    virtual void debugTurnOff_();
    virtual void debugStop_();
    virtual void debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal);
  private:
    bool _active = false;
    MovingResolver* _movingResolver = NULL;
};

class RoboCarHandlerVerbose: public RoboCarHandler {
  public:
    using RoboCarHandler::RoboCarHandler;
  protected:
    void debugTurnOn_();
    void debugTurnOff_();
    void debugStop_();
    void debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val, uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal);
};

#endif
