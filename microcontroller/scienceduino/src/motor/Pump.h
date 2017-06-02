  //
// Created by matthew on 02/06/17.
//

#ifndef SCIENCEDUINO_PUMP_H
#define SCIENCEDUINO_PUMP_H
#include <Arduino.h>

class Pump {
public:
    Pump(int pin);

    void on();
    void off();
private:
    int pin;
};


#endif //SCIENCEDUINO_PUMP_H
