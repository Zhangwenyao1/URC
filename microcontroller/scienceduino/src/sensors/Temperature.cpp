//
// Created by matthew on 26/05/17.
//

#include "Temperature.h"
#include <SHT1x.h>
#include <Arduino.h>
#include <SensorBase.h>

void Temperature::init() {

}

void Temperature::write() {
    Serial.write(this->id);
    float humid = this->sensor.readTemperatureC();
    Serial.write((char*)&humid, sizeof(float));
}

Temperature::Temperature(int n, SHT1x sensor) : SensorBase(n), sensor(sensor) {}

