/*

# This sample codes is for testing the pH meter V1.0.
#USAGE  rostopic pub /recieve std_msgs/Float32 10  sends to subscriber
rosrun rosserial_python serial_node.py /dev/ttyACM0  reads from the arduino port, you must do this to initaiate the port
rostopic echo /probe shows the ph values
 # Editor : Adam Yang

 # Date   : 2013.10.12

 # Ver    : 0.1

 # Product: pH meter

 # SKU    : SEN0161
 
 rostopic pub /recieve std_msgs/Float32 10
rosrun rosserial_python serial_node.py /dev/ttyACM0

*/
#include <ros.h> // include the ros library
#include <std_msgs/Float32.h> 
#include <std_msgs/String.h>
ros::NodeHandle  nh;
std_msgs::Float32 ph_msg;
ros::Publisher phprobe("probe", &ph_msg);
float check;
void recieved(std_msgs::Float32 &msg) {
  check = msg.data;
  if (check > 5) {
  digitalWrite(13, HIGH);       
delay(300);
  digitalWrite(13, LOW);       
  }
 }
ros::Subscriber<std_msgs::Float32> sub("recieve", &recieved); // 
#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
String tempo;
int buf[10],temp;


//-------------------------------
void setup(){
nh.initNode();
nh.advertise(phprobe);
nh.subscribe(sub);
  pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Ready");    //Test the serial monitor

}
//-------------------------------------------------
void loop()

{

  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value

  { 

    buf[i]=analogRead(SensorPin);

    delay(10);

  }

  for(int i=0;i<9;i++)        //sort the analog from small to large

  {

    for(int j=i+1;j<10;j++)

    {

      if(buf[i]>buf[j])

      {

        temp=buf[i];

        buf[i]=buf[j];

        buf[j]=temp;

      }

    }

  }

  avgValue=0;

  for(int i=2;i<8;i++)                      //take the average value of 6 center sample

    avgValue+=buf[i];

  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt

  phValue=3.5*phValue;                      //convert the millivolt into pH value
/*tempo = Serial.readString();
tempo.toCharArray(probedata, 13);*/
  Serial.print("    pH:");  

  Serial.print(phValue,2);

  Serial.println(" ");
/*  digitalWrite(13, HIGH);*/       
/*Serial.println(probedata);*/
  delay(800);

 /* digitalWrite(13, LOW);*/
ph_msg.data=phValue;
/* changed value to float 32*/
/*remember to run rosrun rosserial_python serial_node.py*/
 phprobe.publish( &ph_msg );
  nh.spinOnce();

}
