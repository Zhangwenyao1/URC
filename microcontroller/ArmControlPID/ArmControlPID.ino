/*General arm control code, featuring PID control for joints 1 through 4, cotrol for the winch and claw
* Note**: that joint1 represents the base and joint2 represents the big arm, so on and so forth
*Tuning constants have not yet been finalized, also pot values may change if the arm stalls or gets stuck
*/

#include <Servo.h>
#include <PID_v1.h>

#define serialBaud 9600
#define victorMin 50
#define victorMax 2350
#define outputMax 100
#define outputMin -100
#define numJoints 6
typedef struct CONSTANTS{
  int motorPins[numJoints] = {
    1,
    2,
    3,
    4,
    5,
    6
  };
  int tiltCamPin = 13;
  int winchPins[3]={
    7,
    8,
    9
  };
  int joint6Pins[3] = {
    10,
    11,
    12
  };
  int potPins[numJoints] ={
    A0,
    A1,
    A2,
    A3
  };
  double j1gains[3] = {
    1, //Kp
    0.0, //Ki
    0.0  //Kd
  };
  double j2gains[3]={
    1,
    0.0,
    0.0
  };
  double j3gains[3]={
    1,
    0.0,
    0.0
  };
  double j4gains[3]={
    1,
    0.0,
    0.0
  };
  double jointPotConstraint[numJoints][2]={
    {0,0},
    {475,10},
    {730,185},
    {685,165}
  };
  double jointAngleConstraint[numJoints][2]={
    {0,0},
    {59,-23},
    {-165,-64},
    {-162,7}
  };
};
typedef struct JOINT{
  double output, input, setpoint;
  Servo motor;
};
//declares a constants structure
CONSTANTS constants;
//declares five instances of the joint structure
JOINT joints[numJoints-1];
//camera tilt servo
Servo tiltCam;
//declares siz PID's and applies the values to the corresponding joints
PID j1PID(&joints[0].input, &joints[0].output, &joints[0].setpoint, constants.j1gains[0], constants.j1gains[1], constants.j1gains[2], DIRECT);
PID j2PID(&joints[1].input, &joints[1].output, &joints[1].setpoint, constants.j2gains[0], constants.j2gains[1], constants.j2gains[2], DIRECT);
PID j3PID(&joints[2].input, &joints[2].output, &joints[2].setpoint, constants.j3gains[0], constants.j3gains[1], constants.j3gains[2], DIRECT);
PID j4PID(&joints[3].input, &joints[3].output, &joints[3].setpoint, constants.j4gains[0], constants.j4gains[1], constants.j4gains[2], DIRECT);
//initiate all of the PIDS
void initPID(){
  //joint 1
  j1PID.SetMode(AUTOMATIC);
  j1PID.SetOutputLimits(outputMin,outputMax);
  //joint 2
  j2PID.SetMode(AUTOMATIC);
  j2PID.SetOutputLimits(outputMin,outputMax);
  //joint 3
  j3PID.SetMode(AUTOMATIC);
  j3PID.SetOutputLimits(outputMin,outputMax);
  //joint 4
  j4PID.SetMode(AUTOMATIC);
  j4PID.SetOutputLimits(outputMin,outputMax);
}
//initiate all of the motors
void initMotors(){
  tiltCam.attach(constants.tiltCamPin);//init the titlCam servo
  for(int i = 0; i<numJoints-1; i++)
    joints[i].motor.attach(constants.motorPins[i]);//init all the joints except the claw
  for(int i =0; i<3; i++){
    pinMode(constants.winchPins[i],OUTPUT);//init the winch
    pinMode(constants.joint6Pins[i],OUTPUT);//init the claw
  }
}
//updates all the pots
void updatePots(){
  for(int i =0; i<numJoints-2; i++)
    joints[i].input = analogRead(constants.potPins[i]);
}
//writes the output of the PID to the motors
void doMotorControl(Servo motor, double output){
  motor.writeMicroseconds(map(output,-100,100,victorMin,victorMax));
}
//enables the compute for the PID's
void computeAllPID(){
  if(!j1PID.Compute()&&!j2PID.Compute()&&!j3PID.Compute()&&!j4PID.Compute()){//all PID must be complete for inotder to stop computing//if any of the PID'S have not reached their desired positions write to motors
    for(int i = 0; i<numJoints-2; i++){//4 PID's == for loops
      if(abs(joints[i].output)>5)//here so that the PID doesn't make the arm jitter and break
        doMotorControl(joints[i].motor, joints[i].output);
    }
  }
}
//maps the input angle to its matching constraints
int mapSetpoints(double angle, int joint){
  return map(angle, constants.jointAngleConstraint[joint][0],constants.jointAngleConstraint[joint][1],constants.jointPotConstraint[joint][0],constants.jointPotConstraint[joint][1]);
}
//constrols the direction of anything wired to L298N
void doL298N(int dir, int enable, int forward, int reverse){
  if(dir == 0)//coast
    digitalWrite(enable,LOW);
  else if(dir == 1){//forward
    digitalWrite(enable,HIGH);
    digitalWrite(forward,HIGH);
  }
  else if(dir == -1){//reverse
    digitalWrite(enable,HIGH);
    digitalWrite(reverse,HIGH);
  }
  else if(dir == 1337){//break
    digitalWrite(enable,HIGH);
    digitalWrite(forward,HIGH);
    digitalWrite(reverse,HIGH);
  }
}
//reads the Serial port and provides new setpoints
void recieveData(){
  String input;
  int commandByte;
  float temp;
  if(Serial.available()){
    Serial.readBytes((char*)&commandByte,sizeof(int));
  }
  switch(commandByte){
    case 1://setpoint byte
      for(int i = 0; i<numJoints;i++){
        Serial.readBytes((char*)&temp,sizeof(float));
        if(i<4)
          joints[i].setpoint = mapSetpoints(temp, i);
        else if(i==4)
          doMotorControl(joints[i].motor,(temp*100));
        else
          doL298N(temp, constants.joint6Pins[0],constants.joint6Pins[1],constants.joint6Pins[2]);
      }
      computeAllPID();
      break;
    case 2://winch byte
      Serial.readBytes((char*)&temp,sizeof(float));
      doL298N(temp,constants.winchPins[0],constants.winchPins[1],constants.winchPins[2]);
      break;
    case 3://camera byte
      Serial.readBytes((char*)&temp,sizeof(float));
      tiltCam.write(temp);
      break;
    case 4://velocity byte
      for(int i = 0; i<numJoints;i++){
        Serial.readBytes((char*)&temp,sizeof(float));
        if(i<5)
          doMotorControl(joints[i].motor, (temp*100));
        else
          doL298N(temp,constants.joint6Pins[0],constants.joint6Pins[1],constants.joint6Pins[2]);
      }
      break;
    case 5://abort byte
      for(int i = 0; i<numJoints;i++){
        if(i<5)
          doMotorControl(joints[i].motor, 0);
        else
          doL298N(temp,constants.joint6Pins[0],constants.joint6Pins[1],constants.joint6Pins[2]);
      }
      doL298N(temp,constants.winchPins[0],constants.winchPins[1],constants.winchPins[2]);
      break;
  }
}

void setup() {
  Serial.begin(serialBaud);
  updatePots();
  initPID();
  initMotors();
}

void loop() {
  updatePots();
  recieveData();
}
