#ifndef PID_h
#define PID_h
#include<math.h>
class PID{
	public:
		PID(double _setPoint, double _Ki, double _Kd, double _kp, double _max, double _min);
		double compute();
		void setError(double _input);
		void setTunningValues(double _Kd, double _Ki, double _Kp);
	private:
		double Ki,Kd,Kp,setPoint,Error,outPut,max,min,Iterm,Dterm,Pterm,input,lastInput;
};
#endif
