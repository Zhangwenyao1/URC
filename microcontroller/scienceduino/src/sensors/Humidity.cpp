//
// Created by matthew on 26/05/17.
//

#include <SHT1x.h>
#include "Humidity.h"

void Humidity::init() {

}

void Humidity::write() {
    Serial.write(this->id);
    float humid = this->sensor->readHumidity();
    Serial.write((char*)&humid, sizeof(float));
}

Humidity::Humidity(int n, SHT1x sensor) : SensorBase(n), sensor(&sensor) {}
