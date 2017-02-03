#include "Arduino.h"
#include "Motor.h"
#include "Switch.h"
#include "Carousel.h"
#include "ros.h"
#include <std_msgs/UInt16.h>

Motor rotationMotor;
Motor crankMotor;
Switch closedSwitch;
Switch openSwitch;
Switch indexSwitch; 

Carousel::Carousel(Motor _rotate, Motor _crank, Switch _open, Switch _close, Switch _index){
	rotationMotor = _rotate;
	crankMotor = _crank;
	closedSwitch = _close;
	openSwitch = _open;
	indexSwitch = _index;
}
void Carousel::Open(){
	int _Direction;
	_Direction = ((openSwitch.getState() == false) ? 1 : 0);
	crankMotor.doMotor(_Direction);
}
void Carousel::Close(){
	int _Direction;
	_Direction = ((closedSwitch.getState() == false) ? -1 : 0);
	crankMotor.doMotor(_Direction);
}
void Carousel::rotate(std_msgs::UInt16 _index){
	int hold = _index.data;
	int goTo = ((hold + index > 5)?index-hold:index+hold);
	while(index < hold){
		index = ((indexSwitch.getState() == HIGH)? index++ : index);
		rotationMotor.doMotor(1);
	}
}
void Carousel::fillIndex(uint16_t _index){
	fullIndexes[_index] = true;
}
void Carousel::emptyIndex(uint16_t _index){
	fullIndexes[_index] = false;
}
bool Carousel::checkIndex(uint16_t _index){
	return fullIndexes[_index];
}
