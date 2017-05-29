//
// Created by matthew on 28/05/17.
//

#ifndef SCIENCEDUINO_CAROUSEL_H
#define SCIENCEDUINO_CAROUSEL_H

#include <A4988.h>

class Carousel {
public:
    Carousel(A4988 motor);

    bool aligned;
    int index;

    void moveToIndex(int index);
    void recalcAndMove();
    void moveToPh() {
        this->moveToIndex(4);
    }


private:
    A4988 motor;

    int stepsSinceConfirm;
    int reverseDirection;
    bool base;

    int goalIndex;

    int indexToSteps(int ioffset);
    void calculateAligned();

    bool optimalDirection(int to);
};


#endif //SCIENCEDUINO_CAROUSEL_H
