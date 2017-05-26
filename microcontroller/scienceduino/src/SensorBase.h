//
// Created by matthew on 25/05/17.
//

#ifndef SCIENCEDUINO_SENSORBASE_H
#define SCIENCEDUINO_SENSORBASE_H


class SensorBase {
public:
    virtual void write();
    virtual void init();
    SensorBase(int n);
protected:
    int id;
};


#endif //SCIENCEDUINO_SENSORBASE_H
