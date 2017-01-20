#include "Arduino.h"
#include "Encoder.h"
#include "Motor.h"
#include "Potentieometer.h"
#include "Arm.h"

Arm::Arm(Motor[] _joints,Potentiometer[] _pots; Encoder[] _encoder){
	joints=_joints;
	pots = _pots;
	encoders = _encoder;
}

