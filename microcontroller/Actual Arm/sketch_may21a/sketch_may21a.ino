#include <Servo.h>
#define victorMax 2400
#define victorMin 600

struct JOINTPINS{
  int j0 = 9; // wrist roll
  int j1 = 10; // wrist pitch
  int j2 = 11; // small arm
  int j3 = 12;  // big arm
  int j4 = 13;  // base yaw
  int g1 = 8;  // gripper enable
  int g2 = 7;  // gripper open
  int g3 = 6;  // gripper close
  int w1 = 14;  // winch enable
  int w2 = 15;  // winch in
  int w3 = 16;  // winch out
  int camTilt = A0; // camera
}pins;

struct RECIEVED{
  float j0,j1,j2,j3,j4,gripper,winch,camTilt;
}data;

Servo joint0, joint1, joint2, joint3, joint4, camTilt;

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
    Serial.readBytes((char*)&data.gripper,sizeof(float));
    Serial.readBytes((char*)&data.winch,sizeof(float));
    Serial.readBytes((char*)&data.camTilt,sizeof(float));
  }
}
void writeToJoints(){
  joint0.writeMicroseconds(mapToVictor(data.j0));
  joint1.writeMicroseconds(mapToVictor(data.j1));
  joint2.writeMicroseconds(mapToVictor(data.j2));
  joint3.writeMicroseconds(mapToVictor(data.j3));
  joint4.writeMicroseconds(mapToVictor(data.j4));
  camTilt.write(data.camTilt);

  // Gripper Open
  if (data.gripper == 1){
    digitalWrite(pins.g1, HIGH);   // enable pin
    digitalWrite(pins.g2, HIGH);   // turn open on
    digitalWrite(pins.g3, LOW);   // turn close off
  }
  // Gripper Close
  else if (data.gripper == -1){
    digitalWrite(pins.g1, HIGH);   // enable pin
    digitalWrite(pins.g2, LOW);   // turn open off
    digitalWrite(pins.g3, HIGH);   // turn close on
  }
  // Gripper Stop
  else if (data.gripper == 0){
    digitalWrite(pins.g1, LOW);   // enable pin
    digitalWrite(pins.g2, LOW);   // turn open off
    digitalWrite(pins.g3, LOW);   // turn close on
  }

  // Winch In
  if (data.gripper == 1){
    digitalWrite(pins.w1, HIGH);   // enable pin
    digitalWrite(pins.w2, HIGH);   // turn open on
    digitalWrite(pins.w3, LOW);   // turn close off
  }
  // Winch Out
  else if (data.gripper == -1){
    digitalWrite(pins.w1, HIGH);   // enable pin
    digitalWrite(pins.w2, LOW);   // turn open off
    digitalWrite(pins.w3, HIGH);   // turn close on
  }
  // Winch Off
  else if (data.gripper == 0){
    digitalWrite(pins.w1, LOW);   // enable pin
    digitalWrite(pins.w2, LOW);   // turn open off
    digitalWrite(pins.w3, LOW);   // turn close off
  }
  // Winch Break
  else if (data.gripper == 1337){
    digitalWrite(pins.w1, HIGH);   // enable pin
    digitalWrite(pins.w2, HIGH);   // turn open on
    digitalWrite(pins.w3, HIGH);   // turn close on
  }
}
void setup() {
  Serial.begin(9600);
  joint0.attach(pins.j0);
  joint1.attach(pins.j1);
  joint2.attach(pins.j2);
  joint3.attach(pins.j3);
  joint4.attach(pins.j4);
  camTilt.attach(pins.camTilt);
  pinMode(pins.g1, OUTPUT);
  pinMode(pins.g2, OUTPUT);
  pinMode(pins.g3, OUTPUT);
  pinMode(pins.w1, OUTPUT);
  pinMode(pins.w2, OUTPUT);
  pinMode(pins.w3, OUTPUT);
  recievedData();
}

void loop() {
 recievedData();
 writeToJoints();
}
