//
// Created by matthew on 26/05/17.
//

#ifndef SCIENCEDUINO_HUMIDITY_H
#define SCIENCEDUINO_HUMIDITY_H

#include "../SensorBase.h"

class Humidity: public SensorBase {
public:
    Humidity(int n, SHT1x sensor);

    virtual void write();
    virtual void init();
private:
    SHT1x* sensor;
};


#endif //SCIENCEDUINO_HUMIDITY_H
