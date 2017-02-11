#ifndef Winch_h
#define Winch_h
#include "Arduino.h"
#include "Motor.h"
#include <std_msgs/Int16.h>
class Winch{
  public:
    Winch(Motor _winchM);
    void doMotor(std_msgs::Int16 _drive);
  private:
    Motor _motor;
};
#endif
