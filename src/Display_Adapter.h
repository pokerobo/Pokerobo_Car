#ifndef __POKEROBO_CAR_DISPLAY_ADAPTER_H__
#define __POKEROBO_CAR_DISPLAY_ADAPTER_H__

#include "Program_Collection.h"

class DisplayAdapter {
  public:
    DisplayAdapter();
    void begin(bool backlight=true);
    void render(ProgramCollection* programCollection);
    void render(int16_t col, int16_t row, char* text);
    void clear();
  protected:
    void* _lcdRef = NULL;
};

#endif
