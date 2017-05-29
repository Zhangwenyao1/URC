#include <Arduino.h>
#include <SHT1x.h>
#include <A4988.h>
#include "SensorBase.h"
#include "sensors/PH.h"
#include "sensors/Humidity.h"
#include "sensors/Temperature.h"
#include "motor/Carousel.h"
#include "motor/PhProbe.h"
#include "motor/Tube.h"
// Specify data and clock connections and instantiate SHT1x object
#define SHTDataPin  10//black
#define SHTClockPin 11//yellow
SHT1x sht1x(SHTDataPin, SHTClockPin);
A4988 carouselMotor(200, 5, 6, 7);
A4988 phMotor(200, 2, 3, 4);
SensorBase *sensors[3];

Carousel carousel(carouselMotor, 8);
PhProbe phProbe(phMotor, 9);

Servo s;
Tube* tube;

void initializeSensorsAndMotors() {
    carouselMotor.setRPM(70);
    carouselMotor.enable();
    //phMotor.setRPM(20);
    //phMotor.enable();
    //phProbe.up();
    sensors[0] = new PH(0);
    sensors[1] = new Temperature(1, sht1x);
    sensors[2] = new Humidity(2, sht1x);
    carousel.home();
    s.attach(12);
    tube = new Tube(s);
}

void setup() {
    Serial.begin(38400); // Open serial connection to report values to host
    initializeSensorsAndMotors();
}

void writeData() {
    for (int i =0; i < 3; i++) {
        sensors[i]->write();
    }
}


void readInputs() {
    if (Serial.available() > 0) {
        byte cmd = (byte) Serial.read();
        if (cmd == 0x00) {
            int index = Serial.read();
            carousel.moveToIndex(index);
            Serial.write(0x05);
        }
        else if (cmd == 0x01) {
            int index = Serial.read();
            carousel.moveToPh(index);
            Serial.write(0x05);
        }
        else if (cmd == 0x02) {
            tube->open();
        }
        else if (cmd == 0x03) {
            tube->close();
        }
        else if (cmd == 0x04) {
            //phProbe.up();
        }
        else if (cmd == 0x05) {
            //phProbe.down();
        }
    }
}

void loop() {
    //doSteppers();
    readInputs();
    writeData();
    //readInputs();
}
