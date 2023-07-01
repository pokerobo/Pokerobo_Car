#include <Servo.h>

#ifndef __PEDESTAL_HANDLER_H__
#define __PEDESTAL_HANDLER_H__

#define HORIZONTAL_SERVO_PIN  4
#define VERTICAL_SERVO_PIN    5

#define MOVING_AMOUNT         5

class PedestalHandler {
  public:
    PedestalHandler(int hPin=HORIZONTAL_SERVO_PIN, int vPin=VERTICAL_SERVO_PIN, bool debugEnabled=true);
    void begin(int hMinAngle=0, int hMaxAngle=180, int vMinAngle=0, int vMaxAngle=180);
    void reset();
    void test();

    bool verticalServoUp();
    bool verticalServoDown();
    bool horizontalServoLeft();
    bool horizontalServoRight();  

    int changeHorizontalServo(int hDelta);
    int changeVerticalServo(int vDelta);
    bool change(int hDelta, int vDelta);
    int getHorizontalPosition();
    void setHorizontalPosition(int hPos);
    int updateHorizontalPosition(int hPos, int hCurrentPos = -1);
    int getVerticalPosition();
    void setVerticalPosition(int vPos);
    int updateVerticalPosition(int vPos, int vCurrentPos = -1);
    bool syncWith(PedestalHandler master);

  private:
    int count;
    Servo horizontalServo;
    int horizontalServoPin;
    int horizontalMinAngle;
    int horizontalMaxAngle;
    Servo verticalServo;
    int verticalServoPin;
    int verticalMinAngle;
    int verticalMaxAngle;
    bool debugEnabled;
};

#endif
