#include "Moving_Resolver.h"

#define BOUND_X    40
#define BOUND_Y    40

MovingCommand* MovingResolver::resolve(MovingCommand* packet, int x, int y) {
  if (packet == NULL) {
    return packet;
  }

  uint8_t ld = 0;
  uint8_t rd = 0;
  int enaVal = 0;
  int enbVal = 0;

  if (y > BOUND_Y) {
    ld = rd = 1;
    if (x < -BOUND_X) {
      int r = int_min(int_abs(x), int_abs(y));
      int dx = r * _coeff / 10;
      enaVal = int_abs(y) - (r - dx);
      enbVal = int_abs(y) - dx;
    } else if (x >= -BOUND_X && x <= BOUND_X) {
      enaVal = enbVal = int_abs(y);
    } else {
      int r = int_min(int_abs(x), int_abs(y));
      int dx = r * _coeff / 10;
      enaVal = int_abs(y) - dx;
      enbVal = int_abs(y) - (r - dx);
    }
  } else if (y <= BOUND_Y && y >= -BOUND_Y) {
    // do nothing
  } else {
    ld = rd = 2;
    if (x < -BOUND_X) {
      int r = int_min(int_abs(x), int_abs(y));
      int dx = r * _coeff / 10;
      enaVal = int_abs(y) - (r - dx);
      enbVal = int_abs(y) - dx;
    } else if (x >= -BOUND_X && x <= BOUND_X) {
      enaVal = enbVal = int_abs(y);
    } else {
      int r = int_min(int_abs(x), int_abs(y));
      int dx = r * _coeff / 10;
      enaVal = int_abs(y) - dx;
      enbVal = int_abs(y) - (r - dx);
    }
  }

  enaVal = int_max(enaVal, 0);
  enbVal = int_max(enbVal, 0);

  packet->update(enaVal, ld, enbVal, rd);

  return packet;
}
