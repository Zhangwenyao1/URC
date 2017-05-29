//
// Created by matthew on 29/05/17.
//

#ifndef SCIENCEDUINO_TUBE_H
#define SCIENCEDUINO_TUBE_H

#include <Servo.h>

class Tube {
public:
    Tube(Servo servo);

    void open();
    void close();
private:
    Servo servo;
};


#endif //SCIENCEDUINO_TUBE_H
