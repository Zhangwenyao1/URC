//
// Created by matthew on 25/05/17.
//

#ifndef SCIENCEDUINO_PH_H
#define SCIENCEDUINO_PH_H

#include "../SensorBase.h"


class PH: public SensorBase {
public:
    PH(int n);

    virtual void write();
    virtual void init();
};


#endif //SCIENCEDUINO_PH_H
