#include "Arduino.h"
#include "Potentiometer.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
Potentiometer::Potentiometer(std_msgs::UInt16 _pin){
  pin = _pin;
}
std_msgs::UInt16 Potentiometer::getValue(){
  return map(analogRead(pin),0,1024,0,100);
}
