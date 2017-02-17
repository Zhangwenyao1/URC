#include "PID.h"

PID::PID(double _setPoint, double _Ki, double _Kd, double _kp, double _max, double _min){
	Ki = _Ki;
	Kd = _Kd;
	Kp = _kp;
	max = _max;
	min = _min;
}
double PID::compute(){
	Iterm += (Ki * error);
	Dterm = Kd*(input-lastInput);
	Pterm = Kp * error;
	double sum = Pterm + Iterm - Dterm;
	sum = ((sum>max)?max:sum);
	sum = ((sum<min)?min:sum);
	return sum;
}
void PID::setError(double _input){
	lastInput = input;
	input = _input;
	error = setPoint - input;
}
void PID::setPoint(double _setPoint){
	setPoint =_setPoint;
}
void PID::setTunningValues(double _Kd, double _Ki, double _Kp){
	Kd = _Kd;
	Ki = _Ki;
	Kp = _Kp;
}
