#ifndef Encoder_h
#define Encoder_h
#include "Arduino.h"
class Encoder{
  public:
    Encoder(int A, int B);
    int getEncoderValues();
    void doEncoderA();
    void doEncoderB();
  private:
    int pinA;
    int pinB;
    int countValueA;
    int countValueB;
};
#endif
