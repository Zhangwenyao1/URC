//This is the main arm file
#include "Motor.h";
#include "Encoder.h";
#include "Potentiometer.h";

//motor pins
#define M0 0
#define M1 1
#define M2 2
#define M3 3
#define M4 4
#define M5 5
//motor array constructor
Motor motors[1] = {
  Motor(M0,M1)
};
//pot pins 
#define pot0 A0
#define pot1 A1
#define pot2 A2
#define pot3 A3
//potentiometer array constructor
Potentiometer pots[4]={
  Potentiometer(pot0),
  Potentiometer(pot1),
  Potentiometer(pot2),
  Potentiometer(pot3)  
};

void setup() {
}
void loop(){
}
