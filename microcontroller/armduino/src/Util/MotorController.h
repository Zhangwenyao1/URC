#ifndef MotorController_h
#define MotorController_h
#include <Servo.h>
#include <Arduino.h>
#include "./mathFunc.h"


class MotorController{
	public:
		MotorController(){};
		MotorController(bool type, int pin){
			this->type =  type;
			driver.attach(pin);
		}
		void setDutyCycle(int dutyCycle){
			if(type==true){
				driver.writeMicroseconds(math.dutyCycletoMicroSeconds(victor.min, victor.max, dutyCycle));
			}
			else{
				driver.writeMicroseconds(math.dutyCycletoMicroSeconds(spark.min, spark.max, dutyCycle));
			}
		};
	private:
		struct VICTORSP{
			static const int min = 600;
			static const int max = 2400;
		}victor;
		struct REVSPARK{
			static const int min = 500;
			static const int max = 2500;
		}spark;
		bool type;//false is victor, true is spark
		Servo driver;
		mathFunc math;
};
#endif
