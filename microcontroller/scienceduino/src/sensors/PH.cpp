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
    for (int i=0; i < 20; i++) {
        delay(02);
        avg += analogRead(PH_PIN);
    }
    Serial.write(this->id);
    avg /= 20;
    avg = avg*5.0/1024;
    avg = 3.5 * avg;
    //Serial.println(avg);
    Serial.write((char*)&avg, sizeof(float));
}

PH::PH(int n) : SensorBase(n) {}
