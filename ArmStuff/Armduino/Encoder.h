#ifndef Encoder_h
#define Encoder_h
#include "Arduino.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Encoder{
  public:
	Encoder();
    Encoder(int A, int B);
    uint16_t getEncoderValues();
    void doEncoderA();
    void doEncoderB();
  private:
    int pinA;
    int pinB;
    int countValueA;
    int countValueB;
};
#endif
