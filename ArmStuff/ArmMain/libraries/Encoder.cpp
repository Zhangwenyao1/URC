#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int A, int B){
	pinA = A;
	pinB = B;
	countValue = 0;
}
Encoder::getEncoderValues(){
	return countValue;
}