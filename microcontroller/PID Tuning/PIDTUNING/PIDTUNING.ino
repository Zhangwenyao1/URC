//Gabriel Casciano, May/13/2017
//Use this file to tune PID'S that feature encoders as their source of input

#include <PID_v1.h>
#include <Servo.h>

#define Pi 3.1415
#define totalTicks 1024 //set the total amount of ticks for the pot
#define gearRatio 20 //set the gear ration between the pot and the motor output
#define maxTurns 10 //total turns of the potentiometer
#define motorPin 5 //the motor output pin
#define potPin A0 //potentiometer input pin
#define victorMax 2100 //maximum dutycycle of the victor (full forward)
#define victorMin 500 //minimum dutycycle of the victor (full reverse)
#define inputAngle 90 //the desired angle 

double setpoint, output, input;
double gains[3] = {
  1,
  0,
  0
}; // set your PID tuning gains here

Servo motor;//actual motor declaration

PID motorPID(&input, &output, &setpoint, gains[0], gains[1], gains[2], DIRECT); //PID declaration

void updatePot(){ //this function is used to update the input (the potentiometer)
  input = (double)analogRead(potPin);
}
void setNewPos(){ //this function is used tell the PID the desired setpoint
  setpoint = gearConversion(inputAngle, gearRatio, maxTurns);
}
double gearConversion(double _inputAngle, double _gearRatio, double _maxTurns){//this function is used to compute the output ticks based on the input angle and gear ratio
  double rotation = _gearRatio * _inputAngle /(2*Pi);
  return (totalTicks * rotation / _maxTurns);
}

void motorOutput(){//simply maps the output to the duty cycle acceptable by the victor
  motor.writeMicroseconds(map((output*100),-100,100,victorMin,victorMax));
}

void setup() {
  Serial.begin(9600);//intialize the serial port
  motor.attach(motorPin);//attach the motor to the servo class
  motorPID.SetOutputLimits(-1,1);//set PID output limits (-1,1) so that the motorOutput function can utilize the output
  motorPID.SetMode(AUTOMATIC);//starts and stops the PID automatically
  updatePot();
  setNewPos();//sets the setpoint
}

void loop() {
  updatePot();
  if(!motorPID.Compute())//Compute() returns a bool, whethere or not the PID has reached its setpoint yet
    motorOutput();//write to the motor
}
