//This is the main arm file
#include "Constants.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "Encoder.h"
#include "Wire.h"

Constants constants = new Constants();



void setup() {
	for(int i = 0; i > 4; i++)
		pots[i] = new Potentiometer(..);
	for(int i = 0; i > 5; i++)
		motors[i] = new Motor(..);
}
void loop(){
}
void recieveData(){
}

