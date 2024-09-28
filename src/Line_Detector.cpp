#include "Line_Detector.h"

#include <pcf8574.h>

#define PCF8574_P0 0
#define PCF8574_P1 1
#define PCF8574_P2 2
#define PCF8574_P3 3
#define PCF8574_P4 4
#define PCF8574_P5 5
#define PCF8574_P6 6
#define PCF8574_P7 7

PCF8574 ex0(0x20);

char* LineDetector::toText(uint8_t flag, char* buff, bool asBinDigits) {
  uint8_t len = numOfBits();
  for (int i=0; i<len; i++) {
    if ((flag >> i) & 0b1) {
      buff[i] = asBinDigits ? '1' : '|';
    } else {
      buff[i] = asBinDigits ? '0' : '-';
    }
  }
  buff[len] = '\0';
}

void LineDetector::setBlackLine(bool yes) {
  _blackLine = yes;
}

bool LineDetector::isBlackLine() {
  return _blackLine;
}

uint8_t LineDetector::flip(uint8_t flag) {
  if (!isBlackLine()) {
    return flag;
  }
  if (numOfBits() < 8) {
    uint8_t cutoff = 8 - numOfBits();
    flag = (~flag) & (0xFF >> cutoff);
  } else {
    flag = ~flag;
  }
  return flag;
}

//-------------------------------------------------------------------------------------------------

int LineDetector5Channels::begin() {
  pinMode(ex0, PCF8574_P0, INPUT);
  pinMode(ex0, PCF8574_P1, INPUT);
  pinMode(ex0, PCF8574_P2, INPUT);
  pinMode(ex0, PCF8574_P3, INPUT);
  pinMode(ex0, PCF8574_P4, INPUT);
  return 0;
}

uint8_t LineDetector5Channels::numOfBits() {
  return 5;
}

uint8_t LineDetector5Channels::read(bool raw) {
  uint8_t flag = 0;
  flag |= digitalRead(ex0, PCF8574_P0) << 4;
  flag |= digitalRead(ex0, PCF8574_P1) << 3;
  flag |= digitalRead(ex0, PCF8574_P2) << 2;
  flag |= digitalRead(ex0, PCF8574_P3) << 1;
  flag |= digitalRead(ex0, PCF8574_P4);
  return raw ? flag : flip(flag);
}

//-------------------------------------------------------------------------------------------------

int LineDetector3Channels::begin() {
  pinMode(ex0, PCF8574_P5, INPUT);
  pinMode(ex0, PCF8574_P6, INPUT);
  pinMode(ex0, PCF8574_P7, INPUT);
  return 0;
}

uint8_t LineDetector3Channels::numOfBits() {
  return 3;
}

uint8_t LineDetector3Channels::read(bool raw) {
  uint8_t flag = 0;
  flag |= digitalRead(ex0, PCF8574_P5) << 2;
  flag |= digitalRead(ex0, PCF8574_P6) << 1;
  flag |= digitalRead(ex0, PCF8574_P7) << 0;
  return raw ? flag : flip(flag);
}

//-------------------------------------------------------------------------------------------------

int LineDetector4Channels::begin() {
  pinMode(ex0, PCF8574_P0, INPUT);
  pinMode(ex0, PCF8574_P1, INPUT);
  pinMode(ex0, PCF8574_P2, INPUT);
  pinMode(ex0, PCF8574_P3, INPUT);
  return 0;
}

uint8_t LineDetector4Channels::numOfBits() {
  return 4;
}

uint8_t LineDetector4Channels::read(bool raw) {
  uint8_t flag = 0;
  flag |= digitalRead(ex0, PCF8574_P1) << 3;
  flag |= digitalRead(ex0, PCF8574_P2) << 2;
  flag |= digitalRead(ex0, PCF8574_P3) << 1;
  flag |= digitalRead(ex0, PCF8574_P4);
  return raw ? flag : flip(flag);
}
