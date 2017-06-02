//
// Created by matthew on 29/05/17.
//

#include "PhProbe.h"

PhProbe::PhProbe(A4988 motor, int limitPin): motor(motor), limitPin((uint8_t) limitPin) {
    this->goalState = 0;
    this->in = false;
    this->downProgress = 0;
}

void PhProbe::up() {
    this->goalState = -1;
}

void PhProbe::down() {
    this->goalState = 1;
}

void PhProbe::checkIn() {
    this->in = this->downProgress > 9000;
    //Serial.println(this->downProgress);
    if ((this->in && this->goalState == 1) || (this->downProgress < 30 && this->goalState == -1)) {
        this->goalState = 0;
        //Serial.print("AYAYAYAYAYAYAYA");
    }
}

void PhProbe::limitPush() {
    this->downProgress = 0;
    this->checkIn();
    this-> goalState = 0;
}

void PhProbe::move() {
    if (this->goalState != 0) {
        this->motor.move(this->goalState);
        this->downProgress += this->goalState;
    }
}

void PhProbe::update() {
    this->checkIn();
    while (this->goalState != 0) {
        this->checkIn();
        this->move();
    }
}

