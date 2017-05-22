#ifndef mathFunc_h
#define mathFunc_h
#include <Arduino.h>
#include "../Constants.h"

class mathFunc{
	public:
		mathFunc(){};
		Constants constant = Constants();
		float degToRad(float _val){
			return ((_val*constant.Pi)/180);
		};
		float radToDegrees(float _val){
			return ((_val*180)/constant.Pi);
		};
		float toFloat(int _val){
			return((_val)/(10^7));
		};
		float calcGripperDistance(float distance, float stepsPer){
			return (distance*stepsPer);
		};
		int dutyCycletoMicroSeconds(int maxSeconds, int minSeconds, int dutyCycle){
			return map((dutyCycle*100),-100,100,minSeconds,maxSeconds);
		};
		int jointConversions(double gearRatio, float inputAngle, double turns, int minTicks){
			int out = ((inputAngle/(2*constant.Pi))*(constant.totalTicks/turns)*gearRatio);
			return out + minTicks;
		};
};
#endif
