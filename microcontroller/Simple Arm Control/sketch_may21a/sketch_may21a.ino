#include <Servo.h>
#define victorMax 2600
#define victorMin 600

struct JOINTPINS{
  int j0 = 1;
  int j1 = 2;
  int j2 = 3;
  int j3 = 4;
  int j4 = 5;
  int j5 = 6; 
  int camTilt = 7;
}pins;

struct RECIEVED{
  float j0,j1,j2,j3,j4,j5,camTilt;
}data;

Servo joint0, joint1, joint2, joint3, joint4, joint5, camTilt;

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
  camTilt.attach(pins.camTilt);
  recievedData();
}

void loop() {
 recievedData();
 writeToJoints();
}
