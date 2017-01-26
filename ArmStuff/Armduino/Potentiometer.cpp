#include "Arduino.h"
#include "Potentiometer.h"
Potentiometer::Potentiometer(int _pin){
  pin = _pin;
}
uint16_t Potentiometer::getValue(){
  return map(analogRead(pin),0,1024,0,100);
}


