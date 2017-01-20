#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int A, int B){
  pinA = A;
  pinB = B;
  countValueA = 0;
  countValueB = 0;
}
int Encoder::getEncoderValues(){
	int value = (countValueA+countValueB)/2;
	return (value > 0) ? (value):(1);
}
void Encoder::doEncoderA(){
	countValueA++;
}
void Encoder::doEncoderB(){
	countValueB++;
}
