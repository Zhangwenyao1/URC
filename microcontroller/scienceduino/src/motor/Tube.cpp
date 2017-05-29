//
// Created by matthew on 29/05/17.
//

#include "Tube.h"

Tube::Tube(Servo servo): servo(servo) {
}

void Tube::open() {
    this->servo.write(255);
}

void Tube::close() {
    this->servo.write(0);
}
