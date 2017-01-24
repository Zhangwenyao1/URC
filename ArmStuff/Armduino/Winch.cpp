#include "Arduino.h"
#include "Winch.h"
#include "Motor.h"

Motor motor;

Winch::Winch(int m1, int dir1){
	Motor motor = Motor(m1,dir1);
}
void Winch::doMotor(bool _drive){
	motor.doMotor(_drive);
}
