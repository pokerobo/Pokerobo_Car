#ifndef __POKEROBO_CAR_RF24_LISTENER_H__
#define __POKEROBO_CAR_RF24_LISTENER_H__

#include "Commons.h"
#include "Input_Listener.h"
#include "Input_Controller.h"

#ifndef __RF24_LOADING_LOG__
#define __RF24_LOADING_LOG__  __LOADING_LOG_ENABLED__
#endif//__RF24_LOADING_LOG__

#ifndef __RF24_RUNNING_LOG__
#define __RF24_RUNNING_LOG__  __RUNNING_LOG_ENABLED__
#endif//__RF24_RUNNING_LOG__

#ifndef __INPUT_RUNNING_LOG__
#define __INPUT_RUNNING_LOG__  __RF24_RUNNING_LOG__
#endif//__INPUT_RUNNING_LOG__

#ifndef __RF24_BINARY_ENCODING__
#define __RF24_BINARY_ENCODING__  1
#endif

#ifndef __RF24_MESSAGE_LENGTH__
#define __RF24_MESSAGE_LENGTH__   32
#endif

#ifndef __RF24_DEFAULT_ADDRESS__
#define __RF24_DEFAULT_ADDRESS__  0x123456789ABCDEF0LL
#endif

#ifndef __RF24_CE_PIN__
#define __RF24_CE_PIN__           9
#endif

#ifndef __RF24_CSN_PIN__
#define __RF24_CSN_PIN__          10
#endif

#define RF24_JOYSTICK_DEADZONE_X  32
#define RF24_JOYSTICK_DEADZONE_Y  32

#define RF24_JOYSTICK_RANGE_X     255
#define RF24_JOYSTICK_RANGE_Y     255

class RF24Listener: public CarDebugLoggable, public InputListener, public InputController {
  public:
    RF24Listener(uint64_t address=__RF24_DEFAULT_ADDRESS__, bool debugEnabled=true);
    void begin();
    int read(MasterContext* context, JoystickAction* action, MovingCommand* command);
    int loop();
    void set(HangingDetector* hangingDetector);
  protected:
    bool available();
    bool isDebugEnabled();
    CarDebugLogger* getLogger();
    bool isJoystickChanged(int, int);
    int adjustJoystickX(int nJoyX);
    int adjustJoystickY(int nJoyY);
    virtual void debugAvailable_(bool& tx_ok, bool& tx_fail, bool& rx_ready, bool ok);
    virtual void debugJoystickControl_(bool ok, JoystickAction* action);
  private:
    uint64_t _address = __RF24_DEFAULT_ADDRESS__;
    HangingDetector* _hangingDetector = NULL;
};

class RF24ListenerVerbose: public RF24Listener {
  protected:
    void debugAvailable_(bool& tx_ok, bool& tx_fail, bool& rx_ready, bool ok);
    void debugJoystickControl_(bool ok, JoystickAction* action);
};

#endif
