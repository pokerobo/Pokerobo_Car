#ifndef __ROBOCAR_DANCING_PUPPET_H__
#define __ROBOCAR_DANCING_PUPPET_H__

#include "Pokerobo_Arm.h"
#include "Pokerobo_Car.h"

class DancingPuppetCar: public RemoteControlCar {
  public:
    // BEGIN: overriding
    uint8_t getId();
    int begin();
    int check(void* action, void* command);
    int close();
    // END: overriding
    DancingPuppetCar(char* title,
        DisplayAdapter* displayAdapter=NULL,
        RoboCarHandler* roboCarHandler=NULL,
        PedestalGroup* pedestalGroup=NULL,
        bool autoPedestal=false): RemoteControlCar(title,
            displayAdapter,
            roboCarHandler) {
              _pedestalGroup = pedestalGroup;
              _autoPedestal = autoPedestal;
            };
    void set(DisplayAdapter* displayAdapter);
    void set(RoboCarHandler* roboCarHandler);
    void set(PedestalGroup* pedestalGroup, bool autoPedestal=false);
  private:
    PedestalGroup* _pedestalGroup = NULL;
    bool _autoPedestal = false;
};

#endif
