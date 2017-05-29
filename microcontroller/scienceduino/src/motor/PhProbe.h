//
// Created by matthew on 29/05/17.
//

#ifndef SCIENCEDUINO_PHPROBE_H
#define SCIENCEDUINO_PHPROBE_H


#include <A4988.h>

class PhProbe {
public:
    PhProbe(A4988 motor, int limitPin);

    void up();
    void down();

    int downProgress;
    bool in;

    void update();
private:
    int goalState;
    A4988 motor;

    uint8_t limitPin;

    void checkIn();
    void limitPush();
    void move();
};


#endif //SCIENCEDUINO_PHPROBE_H
