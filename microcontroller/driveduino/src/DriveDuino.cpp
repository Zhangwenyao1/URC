//driveduino
#include "Arduino.h"
#include <Encoder.h>
#include <PID.h>

#include "Motor.h"
#include "Encoder.h"

//Left Motor pins
#define _leftFront 0
#define _leftMid 1
#define _leftRear 2

//Left Direction Pins
#define _leftFrontD 3
#define _leftMidD 4
#define _leftRearD 5


//Right Motor Pins
#define _rightFront 6
#define _rightMid 7
#define _rightRear 8

//Right Direction Pins
#define _rightFrontD 9
#define _rightMidD	10
#define _rightReadD 11

//Motor Declarations
Motor leftFrontMotor = Motor(_leftFront);
Motor leftMidMotor = Motor(_leftMid);
Motor leftRearMotor = Motor(_leftRear);
Motor rightFrontMotor = Motor(_rightFront);
Motor rightMidMotor = Motor(_rightMid);
Motor rightRearMotor = Motor(_rightRear);


//left encoder pins
#define _lfEncA 12
#define _lfEncB 13
#define _lmEncA 14
#define _lmEncB 15
#define _lrEncA 16
#define _lrEncB 17
//right encoder pins
#define _rfEncA 18
#define _rfEncB 19
#define _rmEncA 20
#define _rmEncB 21
#define _rrEncA 22
#define _rrEncB 23

void setup() {

}
void loop() {

}

