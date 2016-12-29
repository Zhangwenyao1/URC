#ifndef Constants_h
#define Constants_h

#include "Arduino.h"

class Constants{
  public:
    Constants();
    int getValue(String _key);
  private:
	int M0;
    int M1;
    int M2;
    int M3;
    int M4;
    int M5;
    int pot0;
    int pot1;
    int pot2;
    int pot3;
    int enca0;
    int encb0;
};
#endif
