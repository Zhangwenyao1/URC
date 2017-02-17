#include "PID.h"

PID::PID(float _Ki, float _Kd, float _kp, float _max, float _min){
	Ki = _Ki;
	Kd = _Kd;
	Kp = _kp;
	max = _max;
	min = _min;
	setPoint;
	error;
	Iterm;
	Dterm;
	Pterm;
	lastInput;
	input;
}
float PID::compute(){
	Iterm += (Ki * error);
	Dterm = Kd*(input-lastInput);
	Pterm = Kp * error;
	float sum = Pterm + Iterm - Dterm;
	sum = ((sum>max)?max:sum);
	sum = ((sum<min)?min:sum);
	return sum;
}
bool PID::isDone(){
	return ((error == 0)?true:false);
}
void PID::setError(float _input){
	lastInput = input;
	input = _input;
	error = setPoint - input;
}
void PID::init(float _setPoint){
	setPoint =_setPoint;
	Iterm =0;
	Dterm =0;
	Pterm =0;
	error =0;
	lastInput =0;
	input =0;
}
void PID::setTunningValues(float _Kd, float _Ki, float _Kp){
	Kd = _Kd;
	Ki = _Ki;
	Kp = _Kp;
}
