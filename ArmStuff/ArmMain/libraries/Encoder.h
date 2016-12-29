#ifndef Encoder_h
#define Encoder_h
#include "Arduino.h"
class Encoder{
	public:
		Encoder(int A, int B);
		int getEncoderValues();
		int doEncoders();
	private:
		int pinA;
		int pinB;
		int countValue;
};
#endif