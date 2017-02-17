#ifndef PID_h
#define PID_h
class PID{
	public:
		PID(float _Ki, float _Kd, float _kp, float _max, float _min);
		float compute();
		void setError(float _input);
		void setTunningValues(float _Kd, float _Ki, float _Kp);
		void init(float _setPoint);
		bool isDone();
	private:
		float Ki,Kd,Kp,setPoint,Error,outPut,max,min,Iterm,Dterm,Pterm,input,lastInput;
};
#endif
