#include "Pokerobo_Car_quick_start.h"

QuickStartLauncher launcher;

void setup() {
  Serial.begin(57600);
  launcher.begin(1);
}

void loop() {
  launcher.check();
}
