//This is the main arm file
#include "Constants.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "Encoder.h"
#include "Wire.h"

Constants constants = new Constants();
Motor motors[] = new Motor[];
Potentiometer pots = new Potentiometer[];

int potValues[] = new int[4];//contains the current position of the pots
int encoderValues[] = new int[2];//contains the current count values for the encoders channels
int motorOutputs[][] = new int[5][2];//contains the motor outputs and their directions

void setup() {
}
void loop() {
}
void recieveData(){
	
}

