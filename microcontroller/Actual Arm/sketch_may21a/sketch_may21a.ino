#include <Servo.h>
#define victorMax 2600
#define victorMin 600

struct JOINTPINS{
  int j0 = 9; // wrist roll
  int j1 = 10; // wrist pitch
  int j2 = 11; // small arm
  int j3 = 12;  // big arm
  int j4 = 13;  // base yaw
  int j5 = 8;  // gripper
  int j6 = 15;  // winch
  int camTilt = A0; // camera
}pins;

struct RECIEVED{
  float j0,j1,j2,j3,j4,j5,j6,camTilt;
}data;

Servo joint0, joint1, joint2, joint3, joint4, joint5, joint6, camTilt;

int mapToVictor(float input){
  return map((input*100),-100,100,victorMin,victorMax);
}
void recievedData(){
  if(Serial.available()>=sizeof(float)){
    Serial.readBytes((char*)&data.j0,sizeof(float));
    Serial.readBytes((char*)&data.j1,sizeof(float));
    Serial.readBytes((char*)&data.j2,sizeof(float));
    Serial.readBytes((char*)&data.j3,sizeof(float));
    Serial.readBytes((char*)&data.j4,sizeof(float));
    Serial.readBytes((char*)&data.j5,sizeof(float));
    Serial.readBytes((char*)&data.j6,sizeof(float));
    Serial.readBytes((char*)&data.camTilt,sizeof(float));
  }
}
void writeToJoints(){
  joint0.writeMicroseconds(mapToVictor(data.j0));
  joint1.writeMicroseconds(mapToVictor(data.j1));
  joint2.writeMicroseconds(mapToVictor(data.j2));
  joint3.writeMicroseconds(mapToVictor(data.j3));
  joint4.writeMicroseconds(mapToVictor(data.j4));
  joint5.writeMicroseconds(mapToVictor(data.j5));
  joint6.writeMicroseconds(mapToVictor(data.j6));
  camTilt.write(data.camTilt);
}
void setup() {
  Serial.begin(9600);
  joint0.attach(pins.j0);
  joint1.attach(pins.j1);
  joint2.attach(pins.j2);
  joint3.attach(pins.j3);
  joint4.attach(pins.j4);
  joint5.attach(pins.j5);
  joint6.attach(pins.j6);
  camTilt.attach(pins.camTilt);
  recievedData();
}

void loop() {
 recievedData();
 writeToJoints();
}
