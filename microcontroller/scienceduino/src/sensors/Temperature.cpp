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
    float temp = this->sensor->readTemperatureC();
    //Serial.println(temp);
    Serial.write((char*)&temp, sizeof(float));
}

Temperature::Temperature(int n, SHT1x sensor) : SensorBase(n), sensor(&sensor) {}

