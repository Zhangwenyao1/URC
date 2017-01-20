#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int A){
  pinA = A;
  countValue = 0;
}
int Encoder::getEncoderValues(){
  return countValue;
}
void Encoder::doEncoders(){
  count++;
}

