//Gabriel Casciano, May/13/2017
//Use this file to tune PID'S that feature encoders as their source of input

#include <Arduino.h>
#include <PID_v1.h>
#include <Servo.h>

#define Pi 3.1415
#define totalTicks 1024 //set the total amount of ticks for the pot
#define gearRatio 20 //set the gear ration between the pot and the motor output
#define maxTurns 10 //total turns of the potentiometer
#define motorPin 5 //the motor output pin
#define potPin A0 //potentiometer input pin
#define victorMax 2380 //maximum dutycycle of the victor (full forward)
#define victorMin 600 //minimum dutycycle of the victor (full reverse)
#define inputAngle -0.174533 //the desired angle 
#define fun 12

// min 797
// max 1020
double setpoint, output, input;
double gains[3] = {
  1,
  100,
  1
}; // set your PID tuning gains here

Servo motor;//actual motor declaration

PID motorPID(&input, &output, &setpoint, gains[0], gains[1], gains[2], DIRECT); //PID declaration

double pot_vals[fun] = {0};
double pot_vals_temp[fun] = {0};

void updatePot(){ //this function is used to update the input (the potentiometer)
  for (int i=0; i<fun-1; i++) {
	pot_vals_temp[i+1] = pot_vals[i];
}
  pot_vals_temp[0] = (double)analogRead(potPin);
  memcpy(pot_vals, pot_vals_temp, sizeof(double)*fun);
  double s = 0;
  for (int i =0; i < fun; i++) {
   s += pot_vals[i];
}
  input = s/fun;
}
double gearConversion(double _inputAngle, double _gearRatio, double _maxTurns){//this function is used to compute the output ticks based on the input angle and gear ratio
  double rotation = _gearRatio * _inputAngle /(2*Pi);
  return (totalTicks * rotation / _maxTurns);
}
void setNewPos(){ //this function is used tell the PID the desired setpoint
  setpoint = 950;
}

void motorOutput(){//simply maps the output to the duty cycle acceptable by the victor
  motor.writeMicroseconds(map(-(output*100),-100,100,victorMin,victorMax));
}

void setup() {
  Serial.begin(9600);//intialize the serial port
  motor.attach(motorPin);//attach the motor to the servo class
  motorPID.SetOutputLimits(-1,1);//set PID output limits (-1,1) so that the motorOutput function can utilize the output
  motorPID.SetMode(AUTOMATIC);//starts and stops the PID automatically
  updatePot();
  setNewPos();//sets the setpoint
}

void sendFloat(double d) {
	float f = (float) d;
	char* chars = (char*)&f;
	Serial.write(chars, sizeof(float));
}

void sendCMD() {
       Serial.write(4);
       Serial.write(0);
       sendFloat(input);
       sendFloat(output);
       sendFloat(setpoint);
}

void loop() {
  updatePot();
sendCMD();
if (!motorPID.Compute()) {
  
}
motorOutput();
}
