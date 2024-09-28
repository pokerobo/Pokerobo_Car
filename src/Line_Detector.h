#ifndef __POKEROBO_CAR_LINE_DETECTOR_H__
#define __POKEROBO_CAR_LINE_DETECTOR_H__

#include "Commons.h"

class LineDetector {
  public:
    virtual int begin();
    virtual uint8_t numOfBits();
    virtual uint8_t read(bool raw=false);
    char* toText(uint8_t flag, char* buff, bool asBinDigits=true);
    void setBlackLine(bool yes);
    bool isBlackLine();
  protected:
    uint8_t flip(uint8_t flag);
  private:
    bool _blackLine = true;
};

class LineDetector5Channels: public LineDetector {
  public:
    int begin();
    uint8_t numOfBits();
    uint8_t read(bool raw=false);
};

class LineDetector3Channels: public LineDetector {
  public:
    int begin();
    uint8_t numOfBits();
    uint8_t read(bool raw=false);
};

class LineDetector4Channels: public LineDetector {
  public:
    int begin();
    uint8_t numOfBits();
    uint8_t read(bool raw=false);
};

#endif
