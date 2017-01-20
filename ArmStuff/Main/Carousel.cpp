#include "Arduino.h"
#include "Motor.h"
#include "Switch.h"
#include "Carousel.h"

Carousel::Carousel(Motor _rotationMotor, Motor _crankMotor, Switch _closedSwitch, Switch _openSwitch, Switch _indexSwtich){
	rotationMotor = _rotationMotor;
	crankMotor = _crankMotor;
	closedSwitch = _closedSwitch;
	openSwitch = _openSwitch;
	indexSwitch = _indexSwitch;
}
void Carousel::open(){
	if(openSwitch.getState()==false)
		crankMotor.doMotors(1);
	else
		crankMotor.doMotors(0);
}
void Carousel::close(){
	if(closedSwitch.getState()==false)
		crankMotor.doMotors(-1);
	else
		crankMotor.doMotors(0);
}
void Carousel::rotate(int _index){

}
void Carousel::fillIndex(int _index){

}
bool Carousel::checkIndex(int _index){

}
