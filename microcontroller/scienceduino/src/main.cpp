#include <Arduino.h>
#include <SHT1x.h>
#include "SensorBase.h"
#include "sensors/PH.h"
#include "sensors/Humidity.h"
#include "sensors/Temperature.h"
// Specify data and clock connections and instantiate SHT1x object
#define SHTDataPin  10//black
#define SHTClockPin 11//yellow
SHT1x sht1x(SHTDataPin, SHTClockPin);
SensorBase *sensors[3];

void initializeSensors() {
    sensors[0] = new PH(0);
    sensors[1] = new Temperature(1, sht1x);
    sensors[2] = new Humidity(2, sht1x);
}

void setup() {
    Serial.begin(38400); // Open serial connection to report values to host
    initializeSensors();
}

void doSteppers() {};

void readInputs() {
    for (int i =0; i < 3; i++) {
        sensors[i]->write();
    }
}

void loop() {
    doSteppers();
    readInputs();
}
