#ifndef Encoder_h
#define Encoder_h
#include "Arduino.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Encoder{
  public:
    Encoder(int A, int B);
    std_msgs::UInt16 getEncoderValues();
    void doEncoderA();
    void doEncoderB();
  private:
    int pinA;
    int pinB;
    int countValueA;
    int countValueB;
};
#endif
