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
    this->goalIndex = index;
}

void Carousel::calculateAligned() {
    int errorbar = this->stepsSinceConfirm % 33;
    errorbar = min((33 - errorbar), (errorbar));
    this->aligned = errorbar <= 1;
    if (this->aligned) {
        calculateIndex();
    }
}

void Carousel::calculateIndex() {
    int errorbar = this->stepsSinceConfirm % 33;
    if (errorbar > 15) {
        errorbar = 33-errorbar;
    }
    else {
        errorbar = -errorbar;
    }
    this->index = (this->stepsSinceConfirm + errorbar) / 33;
    if (this->stepsSinceConfirm < 0) {
        this->index += 6;
    }
    if (!this->base) {
        this->index += 3;
    }

    this->index %= 6;
}

int Carousel::optimalDirection(int to) {
    return this->index < to ? 1 : -1;
}

void Carousel::limitPushed() {
    if (this->lastDirection != this->reverseDirection) {
        this->base = !this->base;
    }
    this->stepsSinceConfirm = 0;
    Serial.println("A");
    this->calculateAligned();
}

void Carousel::recalcAndMove() {
    this->calculateAligned();
    if (this->index == this->goalIndex || this->goalIndex == -1) {
        this->goalIndex = -1;
        return;
    }

    this->motor.move(this->optimalDirection(this->goalIndex));
    this->stepsSinceConfirm += this->optimalDirection(this->goalIndex);
}

void Carousel::update() {
    if (digitalRead((uint8_t) this->limitPin) == LOW) {
        this->limitPushed();
    }
    this->recalcAndMove();
}


