//
// Created by matthew on 02/06/17.
//

#include "Pump.h"

Pump::Pump(int pin): pin(pin) {
    pinMode(pin, OUTPUT);
}

void Pump::on() {
    digitalWrite(pin, HIGH);
}

void Pump::off() {
    digitalWrite(pin, LOW);
}