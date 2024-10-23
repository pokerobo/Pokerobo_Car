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

typedef enum POKEROBO_CAR_STATE {
  POKEROBO_CAR_IDLE = 0,
  POKEROBO_CAR_ACTIVE,
  POKEROBO_CAR_RUNNING,
  POKEROBO_CAR_STOPPED,
} pokerobo_car_state_t;

class RoboCarHandler: public CarDebugLoggable {
  public:
    RoboCarHandler(MovingResolver* movingResolver=NULL);
    void set(MovingResolver* movingResolver);
    int begin();
    bool isIdle();
    bool isActive();
    void turnOn();
    void turnOff();
    void toggle();
    void stop();
    void move(int x, int y, bool reversed = false);
    void move(int8_t leftDirection, int leftSpeed,
        int rightSpeed, int8_t rightDirection,
        bool reversed = false);
    void move(MovingCommand* packet);
    pokerobo_car_state_t getState();
  protected:
    void updateState_(uint8_t in1Val, uint8_t in2Val,
        uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal);
    void writeL298nPins_(uint8_t in1Val, uint8_t in2Val,
        uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal);
    virtual void debugTurnOn_(pokerobo_car_state_t prevState);
    virtual void debugTurnOff_(pokerobo_car_state_t prevState);
    virtual void debugStop_(pokerobo_car_state_t prevState);
    virtual void debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val,
        uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal, pokerobo_car_state_t prevState);
  private:
    pokerobo_car_state_t _state = POKEROBO_CAR_IDLE;
    MovingResolver* _movingResolver = NULL;
};

class RoboCarHandlerVerbose: public RoboCarHandler {
  public:
    using RoboCarHandler::RoboCarHandler;
  protected:
    void debugTurnOn_(pokerobo_car_state_t prevState);
    void debugTurnOff_(pokerobo_car_state_t prevState);
    void debugStop_(pokerobo_car_state_t prevState);
    void debugWriteL298nPins_(uint8_t in1Val, uint8_t in2Val,
        uint8_t in3Val, uint8_t in4Val,
        int enaVal, int enbVal, pokerobo_car_state_t prevState);
};

#endif
