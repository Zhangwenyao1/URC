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
    this->goalState = 1;
}

void PhProbe::down() {
    this->goalState = -1;
}

void PhProbe::checkIn() {
    this->in = this->downProgress > 200;
}

void PhProbe::limitPush() {
    this->downProgress = 0;
    this->checkIn();
    if (this->goalState == 1) {
        this->goalState = 0;
    }
}

void PhProbe::move() {
    if (this->goalState != 0) {
        this->motor.move(this->goalState);
        this->downProgress += this->goalState;
    }
}

void PhProbe::update() {
    if (digitalRead(this->limitPin) == LOW) {
        this->limitPush();
    }
    this->move();
}

