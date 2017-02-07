#ifndef Winch_h
#define Winch_h
#include "Arduino.h"
#include "Motor.h"
#include <std_msgs/Float32.h>
class Winch{
  public:
    Winch(Motor _winchM);
    void doMotor(std_msgs::Float32 _drive);
  private:
    Motor _motor;
};
#endif
