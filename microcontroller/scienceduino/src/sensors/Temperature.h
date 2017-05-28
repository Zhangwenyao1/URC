//
// Created by matthew on 26/05/17.
//

#ifndef SCIENCEDUINO_TEMPERATURE_H
#define SCIENCEDUINO_TEMPERATURE_H


#include <SensorBase.h>
#include <SHT1x.h>

class Temperature: public SensorBase {
public:
    Temperature(int n, SHT1x sensor);
    virtual void init();
    virtual void write();

private:
    SHT1x* sensor;
};


#endif //SCIENCEDUINO_TEMPERATURE_H
