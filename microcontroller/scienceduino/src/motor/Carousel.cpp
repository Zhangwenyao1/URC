//
// Created by matthew on 28/05/17.
//

#include "Carousel.h"
#include <A4988.h>

Carousel::Carousel(A4988 motor, int limitPin): motor(motor), limitPin(limitPin) {
    this->aligned = true; // Assume we are aligned at the base = true setpoint (0)
    this->index = 0;
    this->base = true;
    this->reverseDirection = 0;
    this->stepsSinceConfirm = 0;
    this->goalIndex = -1;

    pinMode((uint8_t) limitPin, INPUT);
}

void Carousel::moveToIndex(int index) {
   // Serial.print("HOME");
    this->home();
    // Serial.print("TO ");
    // Serial.println(index);
    this->motor.enable();
    this->goalIndex = (index + 3)%6;
    this->motor.rotate(this->getShortDirection()*2);
    float x = (0.270833333407*(index^4))+(-2.5324074*(index^3))+(6.40972222*(index^2))+(-2.83862433*index)+2.115079;
    //this->motor.rotate()
    this->index = index;
    this->motor.disable();
}

int Carousel::dirToSteps(int v) {
    return (360/6)*v;
}

int Carousel::getShortDirection() {
    return -dirToSteps(this->goalIndex);
}

void Carousel::home() {
    this->motor.enable();
   // Serial.print("HOMES");
    while (digitalRead((uint8_t) this->limitPin) == HIGH) {
        this->motor.move(-1);
        delay(5);
    }
   // Serial.println("is done");
    this->index = 0;
    this->motor.move(-10);
    this->motor.disable();

}




