//Main Arm Code, Ryerson Rams Robotics, URC2017
#include "Motor.h";
#include "Encoder.h";
#include "Potentiometer.h";
#include <Wire.h>
//I2C addresses
#define arm 2
#define master 1

//motor pins
#define M0 0
#define M1 1
#define M2 2
#define M3 3
#define M4 4
#define M5 5
//motor array constructor
Motor motors[1] = {
  Motor(M0,M1)//NOT COMPLETE
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
void setup(){
  Wire.begin(2);
  Wire.onReceive(event);
}
void event(int dataIn){
  while(1<Wire.available()){
    switch(Wire.read()){
      case 0://motor 0
        motors[0].doMotors(Wire.requestFrom(master, 3, true));
    }
  }
}
void loop(){
}
