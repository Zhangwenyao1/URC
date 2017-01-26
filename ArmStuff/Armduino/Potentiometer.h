#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Potentiometer{
  public:
    Potentiometer(int _pin);
    std_msgs::UInt16 getValue();
  private:
    int pin;
};
#endif
