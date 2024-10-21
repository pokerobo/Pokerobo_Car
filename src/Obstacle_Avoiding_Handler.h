#ifndef __POKEROBO_CAR_OBSTACLE_AVOIDING_HANDLER_H__
#define __POKEROBO_CAR_OBSTACLE_AVOIDING_HANDLER_H__

#include "RoboCar_Handler.h"
#include "Untrasonic_Reader.h"

#define RC_SPEED                      200
#define RC_MOVING_BACKWARD_TIME       500
#define RC_TURN_LR_TIME               500
#define RC_MIN_DISTANCE_TO_OBSTACLE    20
#define DEFAULT_PROBE_ROTATION_ANGLE   80
#define DEFAULT_SERVO_POSITION_ANGLE   90

class ObstacleAvoidingHandler {
  public:
    ObstacleAvoidingHandler(RoboCarHandler *carHandler,
        UntrasonicReader *sonar=NULL, void *servo=NULL);
    void begin();
    virtual bool willBeCollided();
    virtual uint32_t detectObstacle();
    virtual void move();
    void setProbeRotationAngle(byte angle);
    void setSonarDefaultPositionAngle(byte angle);
    void setMinDistanceToObstacle(uint16_t distance);
    void setMovingBackwardDuration(uint16_t duration);
    void setTurnLeftDuration(uint16_t duration);
    void setTurnRightDuration(uint16_t duration);
    void setWheelSpeed(byte speed);
  protected:
    uint32_t lookLeft();
    uint32_t lookRight();
    void attachServo(byte pin);
    void rotateServo(byte angle);
    void setupSonar();
    void turnLeft();
    void turnRight();
    void moveForward();
    void moveBackward();
    void moveStop();
  private:
    uint32_t _distance = 0;
    uint32_t _prevDistance = 0;
    RoboCarHandler *_roboCarHandler = NULL;
    UntrasonicReader *_sonar = NULL;
    void *_servo = NULL;
    byte _probeRotationAngle = DEFAULT_PROBE_ROTATION_ANGLE;
    byte _sonarDefaultPositionAngle = DEFAULT_SERVO_POSITION_ANGLE;
    uint16_t _minDistanceToObstacle = RC_MIN_DISTANCE_TO_OBSTACLE;
    uint16_t _movingBackwardDuration = RC_MOVING_BACKWARD_TIME;
    uint16_t _turnLeftDuration = RC_TURN_LR_TIME;
    uint16_t _turnRightDuration = RC_TURN_LR_TIME;
    byte _wheelSpeed = RC_SPEED;
};

#endif
