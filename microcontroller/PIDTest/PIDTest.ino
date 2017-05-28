#include <Servo.h>
#include <PID_v1.h>

#define potPin A0
#define motorPin 13
#define victorMax 2300
#define victorMin 600

double output, input, setpoint=400;
double Kp=1.5, Ki, Kd;
Servo motor;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void updatePot(){
  input = analogRead(potPin);
  Serial.print(input);
  Serial.print(", ");
}

void doMotors(){
  if(abs(output)>5)
    motor.writeMicroseconds(map(output,-100,100,victorMin,victorMax));
  Serial.println(output);
}

void setup() {
  Serial.begin(9600);
  motor.attach(motorPin);
  pid.SetOutputLimits(-100,100);
  pid.SetMode(AUTOMATIC);
  updatePot();
}
void loop() {
  updatePot();
  if(!pid.Compute())
    doMotors();
}
