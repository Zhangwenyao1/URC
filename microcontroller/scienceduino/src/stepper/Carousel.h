//
// Created by matthew on 28/05/17.
//

#ifndef SCIENCEDUINO_CAROUSEL_H
#define SCIENCEDUINO_CAROUSEL_H

#include <A4988.h>
#include <Arduino.h>

class Carousel {
public:
    Carousel(A4988 motor, int limitPin);

    bool aligned;
    int index;

    void moveToIndex(int index);
    void moveToPh(int index) {
        this->moveToIndex((index + 2) % 6);
    }
    void update();


private:
    A4988 motor;

    int stepsSinceConfirm;
    int reverseDirection;
    int lastDirection;
    int limitPin;
    bool base;

    int goalIndex;

    void calculateAligned();
    void calculateIndex();
    void recalcAndMove();
    void limitPushed();

    int optimalDirection(int to);
};


#endif //SCIENCEDUINO_CAROUSEL_H
