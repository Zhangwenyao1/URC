#include <Arduino.h>
#include <SHT1x.h>
#include <A4988.h>
#include "SensorBase.h"
#include "sensors/PH.h"
#include "sensors/Humidity.h"
#include "sensors/Temperature.h"
#include "stepper/Carousel.h"
// Specify data and clock connections and instantiate SHT1x object
#define SHTDataPin  10//black
#define SHTClockPin 11//yellow
SHT1x sht1x(SHTDataPin, SHTClockPin);
A4988 carouselMotor(200, 2, 3, 4);
SensorBase *sensors[3];

Carousel carousel(carouselMotor, 8);

void initializeSensors() {
    carouselMotor.setRPM(50);
    carouselMotor.enable();
    sensors[0] = new PH(0);
    sensors[1] = new Temperature(1, sht1x);
    sensors[2] = new Humidity(2, sht1x);
    carousel.moveToIndex(1);
}

void setup() {
    Serial.begin(38400); // Open serial connection to report values to host
    initializeSensors();
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
}

void doSteppers() {
    carousel.update();
};

void readInputs() {
    for (int i =0; i < 3; i++) {
        sensors[i]->write();
    }
}

void loop() {
    doSteppers();
    //readInputs();
}
