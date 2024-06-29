#include "Display_Adapter.h"

#include <LiquidCrystal_I2C.h>

DisplayAdapter::DisplayAdapter() {
  _lcdRef = new LiquidCrystal_I2C(0x27, 16, 2);
}

void DisplayAdapter::begin(bool backlight) {
  LiquidCrystal_I2C* lcd = (LiquidCrystal_I2C*)_lcdRef;
  lcd->init();
  lcd->clear();
  if (backlight) {
    lcd->backlight();
  } else {
    lcd->noBacklight();
  }
}

void DisplayAdapter::render(ProgramCollection* programCollection) {
  
}

void DisplayAdapter::render(int16_t col, int16_t row, char* text) {
  if (text != NULL && strlen(text) > 0) {
    LiquidCrystal_I2C* lcd = (LiquidCrystal_I2C*)_lcdRef;
    lcd->setCursor(col, row);
    lcd->print(text);
  }
}

void DisplayAdapter::clear() {
  LiquidCrystal_I2C* lcd = (LiquidCrystal_I2C*)_lcdRef;
  lcd->clear();
}
