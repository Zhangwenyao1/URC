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
Servo leftOne;
Servo leftTwo;
Servo leftThree;
Servo rightOne;
Servo rightTwo;
Servo rightThree;
struct DATA {
    float linear;
    float rotation;
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

void recieveData() {
    if (SerialUSB.available() >= sizeof(uint8_t)) {
        delayMicroseconds(10);
        uint8_t cmd = (uint8_t) SerialUSB.read();
        //SerialUSB.print("GOT"); SerialUSB.println(cmd);
        if (cmd == 0 || cmd == 1) {
            inTankDriveMode = (bool) cmd;
        }
        else {
            SerialUSB.readBytes((char *) &received.linear, sizeof(float));
            SerialUSB.readBytes((char *) &received.rotation, sizeof(float));
        }
    }
}

void doMotors(float lin, float rot) {
    if (!inTankDriveMode) {
        setSparkVel((int) ((lin + rot) * 100), (int) ((lin - rot) * -100));
    }
    else{
        setSparkVel((int) (lin * 100), (int) (-rot * 100));
    }
}

void setup() {
    SerialUSB.begin(9600);

    leftOne.attach(pinL1);
    leftTwo.attach(pinL2);
    leftThree.attach(pinL3);
    rightOne.attach(pinR1);
    rightTwo.attach(pinR2);
    rightThree.attach(pinR3);
}

void loop() {
   doMotors(received.linear, received.rotation);
   // SerialUSB.println("ON");
   recieveData();
}

