//
// Created by matthew on 25/05/17.
//

#include "PH.h"
#include <Arduino.h>

#define PH_PIN A0

void PH::init() {

}

void PH::write() {
    float avg = 0;
    for (int i=0; i < 10; i++) {
        delay(10);
        avg += analogRead(PH_PIN);
    }
    Serial.write(this->id);
    avg /= 10;
    Serial.write((char*)&avg, sizeof(float));
}

PH::PH(int n) : SensorBase(n) {}
