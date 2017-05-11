#ifndef mathFunc_h
#define mathFunc_h

#define pi 3.1415

#include <Arduino.h>

class mathFunc{
	public:
		mathFunc(){};
		float degToRad(float _val){
			return ((_val*pi)/180);
		};
		float radToDegrees(float _val){
			return ((_val*180)/pi);
		};
		float toFloat(int _val){
			return((_val)/(10^7));
		};
		int toSteps(float _degrees, float _stepAngle){
			return (int)(_degrees/_stepAngle);
		};
		float calcGripperDistance(float distance, float stepsPer){
			return (distance*stepsPer);
		};
		int dutyCycletoMicroSeconds(int maxSeconds, int minSeconds, int dutyCycle){
			return map((dutyCycle*100),-100,100,maxSeconds,minSeconds);
		};
};
#endif
