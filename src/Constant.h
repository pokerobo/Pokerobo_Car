#ifndef __POKEROBO_CAR_CONFIGURATION_H__
#define __POKEROBO_CAR_CONFIGURATION_H__

#include "Commons.h"

struct ConstantOfCar {
  public:
    static ConstantOfCar* me;
    ConstantOfCar(
      uint8_t pinOfRF24CE_,
      uint8_t pinOfRF24CSN_,
      uint8_t pinOfL298nEnA_,
      uint8_t pinOfL298nIn1_,
      uint8_t pinOfL298nIn2_,
      uint8_t pinOfL298nIn3_,
      uint8_t pinOfL298nIn4_,
      uint8_t pinOfL298nEnB_,
      bool displayBacklight_
    ):
      pinOfRF24CE(pinOfRF24CE_),
      pinOfRF24CSN(pinOfRF24CSN_),
      pinOfL298nEnA(pinOfL298nEnA_),
      pinOfL298nIn1(pinOfL298nIn1_),
      pinOfL298nIn2(pinOfL298nIn2_),
      pinOfL298nIn3(pinOfL298nIn3_),
      pinOfL298nIn4(pinOfL298nIn4_),
      pinOfL298nEnB(pinOfL298nEnB_),
      displayBacklight(displayBacklight_)
    {
      me = this;
    }
    const uint8_t pinOfRF24CE;
    const uint8_t pinOfRF24CSN;
    const uint8_t pinOfL298nEnA;
    const uint8_t pinOfL298nIn1;
    const uint8_t pinOfL298nIn2;
    const uint8_t pinOfL298nIn3;
    const uint8_t pinOfL298nIn4;
    const uint8_t pinOfL298nEnB;
    const bool displayBacklight;
};

#endif
