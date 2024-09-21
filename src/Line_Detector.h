#ifndef __POKEROBO_CAR_LINE_DETECTOR_H__
#define __POKEROBO_CAR_LINE_DETECTOR_H__

#include "Commons.h"

class LineDetector {
  public:
    virtual int begin();
    virtual uint8_t numOfBits();
    virtual uint8_t read();
};

class LineDetector5Channels: public LineDetector {
  public:
    int begin();
    uint8_t numOfBits();
    uint8_t read();
};

#endif
