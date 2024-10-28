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
      uint8_t pinOfTrigger_,
      uint8_t pinOfEcho_,
      uint8_t pinOfServo_,
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
      pinOfTrigger(pinOfTrigger_),
      pinOfEcho(pinOfEcho_),
      pinOfServo(pinOfServo_),
      displayBacklight(displayBacklight_)
    {
      me = this;
    }
    // nRF24
    const uint8_t pinOfRF24CE;
    const uint8_t pinOfRF24CSN;
    // L298N
    const uint8_t pinOfL298nEnA;
    const uint8_t pinOfL298nIn1;
    const uint8_t pinOfL298nIn2;
    const uint8_t pinOfL298nIn3;
    const uint8_t pinOfL298nIn4;
    const uint8_t pinOfL298nEnB;
    // Ultrasonic
    const uint8_t pinOfTrigger;
    const uint8_t pinOfEcho;
    // Servo
    const uint8_t pinOfServo;
    // LCD1602
    const bool displayBacklight;
};

#endif
