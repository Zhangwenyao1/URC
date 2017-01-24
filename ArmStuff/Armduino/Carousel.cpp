#include "Arduino.h"
#include "Motor.h"
#include "Switch.h"
#include "Carousel.h"

Motor rotationMotor;
Motor crankMotor;
Switch closedSwitch;
Switch openSwitch;
Switch indexSwitch; 

Carousel::Carousel(int m1, int m2, int dir1, int dir2, int _pin1, int _pin2, int _pin3){
	Motor rotationMotor = Motor(m1,dir1);
	Motor crankMotor = Motor(m2,dir2);
	Switch closedSwitch = Switch(_pin1);
	Switch openSwitch = Switch(_pin2);
	Switch indexSwitch = Switch(_pin3);
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
void Carousel::rotate(int _index){

}
void Carousel::fillIndex(int _index){
	fullIndexes[_index] = true;
}
void Carousel::emptyIndex(int _index){
	fullIndexes[_index] = false;
}
bool Carousel::checkIndex(int _index){
	return fullIndexes[_index];
}
