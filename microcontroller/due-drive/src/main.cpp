#include <Arduino.h>
#include <Servo.h>

#define pinL1 13
#define pinL2 12
#define pinL3 11
#define pinR1 9
#define pinR2 8
#define pinR3 7
#define sparkMax 2000
#define sparkMin 1000
#define pinZEDServo 2

Servo ZEDServo;
Servo leftOne;
Servo leftTwo;
Servo leftThree;
Servo rightOne;
Servo rightTwo;
Servo rightThree;

struct DATA {
    float linear;
    float rotation;
    float zed_servo;
} received;
bool inTankDriveMode;

void setSparkVel(int left, int right) {
    leftOne.writeMicroseconds(map(left, -100, 100, sparkMin, sparkMax));
    leftTwo.writeMicroseconds(map(left, -100, 100, sparkMin, sparkMax));
    leftThree.writeMicroseconds(map(left, -100, 100, sparkMin, sparkMax));
    rightOne.writeMicroseconds(map(right, -100, 100, sparkMin, sparkMax));
    rightTwo.writeMicroseconds(map(right, -100, 100, sparkMin, sparkMax));
    rightThree.writeMicroseconds(map(right, -100, 100, sparkMin, sparkMax));
}

void setup() {
    SerialUSB.begin(9600);
    leftOne.attach(pinL1);
    leftTwo.attach(pinL2);
    leftThree.attach(pinL3);
    rightOne.attach(pinR1);
    rightTwo.attach(pinR2);
    rightThree.attach(pinR3);
    ZEDServo.attach(pinZEDServo);
}

void loop() {
   if (SerialUSB.available() >= sizeof(uint8_t)) {
       delayMicroseconds(10);
       uint8_t cmd = (uint8_t) SerialUSB.read();
       SerialUSB.print("GOT");
       SerialUSB.println(cmd);
       // TWIST MOTOR COMMAND
       if (cmd == 0) {
           SerialUSB.readBytes((char *) &received.linear, sizeof(float));
           SerialUSB.readBytes((char *) &received.rotation, sizeof(float));
           SerialUSB.print("GOT TWIST ");
           SerialUSB.println((int) received.linear);
           SerialUSB.println((int) received.rotation);
           setSparkVel((int) ((received.linear + received.rotation) * 100), (int) ((received.linear - received.rotation) * -100));
       }
       // TANK MOTOR COMMAND
       else if (cmd == 1) {
           SerialUSB.readBytes((char *) &received.linear, sizeof(float));
           SerialUSB.readBytes((char *) &received.rotation, sizeof(float));
           SerialUSB.print("GOT TANK ");
           SerialUSB.println((int) received.linear);
           SerialUSB.println((int) received.rotation);
           setSparkVel((int) (received.linear * 100), (int) (-received.rotation * 100));
       }
       // ZED SERVO MOTOR COMMAND
       else if (cmd == 2) {
           SerialUSB.readBytes((char *) &received.zed_servo, sizeof(float));
           SerialUSB.print("GOT SERVO ");
           SerialUSB.println((int) received.zed_servo);
           ZEDServo.write((int) received.zed_servo);
       }
   }
}

