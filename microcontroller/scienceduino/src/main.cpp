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
#define SHTDataPin  A1 //black (Humidity / Temperature)
#define SHTClockPin A2 //yellow (Humidity / Temperature)
int PumpPin = 11;
int ServoPin = 12;
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
    phMotor.setRPM(20);
    phMotor.enable();
    phProbe.up();
    sensors[0] = new PH(0);
    sensors[1] = new Temperature(1, sht1x);
    sensors[2] = new Humidity(2, sht1x);
    carousel.home();
    s.attach(ServoPin);
    tube = new Tube(s);
}

void setup() {
    Serial.begin(38400); // Open serial connection to report values to host
    initializeSensorsAndMotors();
    delay(500);
}

void writeData() {
    for (int i =0; i < 3; i++) {
        sensors[i]->write();
    }
}


void readInputs() {
    if (Serial.available() > 0) { // MOVE TO INDEX
        byte cmd = (byte) Serial.read();
        delay(10);
        if (cmd == 0x00) {
            int index = Serial.read();
            //Serial.print(index);
            carousel.moveToIndex(index);
            // Serial.write(0x05);
        }
        else if (cmd == 0x01) { // MOVE TO PH
            int index = Serial.read();
            carousel.moveToPh(index);
            // Serial.write(0x05);
        }
        else if (cmd == 0x02) { // OPEN ETHANOL TUBE
            tube->open();
        }
        else if (cmd == 0x03) { // CLOSE ETHANOL TUBE
            tube->close();
        }
        else if (cmd == 0x04) { // PROBE UP
            phProbe.up();
        }
        else if (cmd == 0x05) { // PROBE DOWN
            phProbe.down();
        }
        else if (cmd == 0x06) { // PUMP DOWN
            // phProbe.down();
        }
        else if (cmd == 0x07) { // PUMP UP
            // phProbe.down();
        }
        while (Serial.available() > 0) {Serial.read();}
    }
}

void loop() {
    readInputs();
    writeData();
}
