//Main Arm Code, Ryerson Rams Robotics, URC2017
#include "Motor.h";
#include "Encoder.h";
#include "Potentiometer.h";
#include "Arm.h"
//I2C addresses
#define arm 2
#define master 1

//motor pins
#define baseM 0
#define elbowM 1
#define wristM 2
#define gripperM 3
#define carouselSpinM 4
#define carouselCrankM 5
#define winchM 6

//direction pins
#define baseDir1 7
#define baseDir2 8
#define elbowDir1 9
#define elbowDir2 10
#define wristDir1 11
#define wristDir2 12
#define gripperDir1 13
#define gripperDir2 14
#define gripperDir1 15
#define gripperDir2 16
#define carouselSpinDir1 17
#define carouselSpinDir2 18
#define carouselCrankDir1 19
#define carouselCrankDir2 20
#define winchDir1 21
#define winchDir2 22

//motor array constructor
Motor motors[1] = {
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
  Serial.begin(9600);
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
