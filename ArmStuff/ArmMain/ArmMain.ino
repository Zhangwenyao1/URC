//This is the main arm file
#include "Motor.h";
//motor pins
#define M0 0
#define M1 1
#define M2 2
#define M3 3
#define M4 4
#define M5 5
//direction pins

//pot pins 
#define pot0 A0
#define pot1 A1
#define pot2 A2
#define pot3 A3
//encoder pins
#define enca0 6
#define encb0 7

Motor motors[1] = {
  Motor(M0,M1)
};
void setup() {
}
void loop(){
}
