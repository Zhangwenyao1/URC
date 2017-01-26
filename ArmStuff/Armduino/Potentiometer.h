#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Potentiometer{
  public:
    Potentiometer(std_msgs::UInt16 _pin);
    std_msgs::UInt16 getValue();
  private:
    std_msgs::UInt16 pin;
};
#endif
