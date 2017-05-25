//ros 
#include <ros.h>
#include <std_msgs/Float32.h>
ros::NodeHandle  nh;
std_msgs::Float32 str_msg;
ros::Publisher chatter("science_publisher", &str_msg);
//humidty/temp setup
#include <SHT1x.h>
// Specify data and clock connections and instantiate SHT1x object
#define dataPin  10
#define clockPin 11
SHT1x sht1x(dataPin, clockPin);

//pH setup
#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

void setup()
{
  //ros
  nh.initNode();
  nh.advertise(chatter);
  //sensors
   Serial.begin(38400); // Open serial connection to report values to host
   Serial.println("Starting up");

  pinMode(13,OUTPUT);  
  //Serial.begin(9600);  
 
}

void loop()
{
  float temp_c;
  float temp_f;
  float humidity;

  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
  Serial.write((char*)(&temp_c), sizeof(float));
  Serial.write((char*)(&humidity), sizeof(float));
  // Print the values to the serial port
  Serial.print("Temperature: ");
  Serial.print(temp_c, DEC);
  Serial.print("C / ");
  Serial.print(temp_f, DEC);
  Serial.print("F. Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  //publish temperature
  str_msg.data = temp_c;
  chatter.publish( &str_msg );
 
  //publish humidity 
  str_msg.data = humidity;
  chatter.publish( &str_msg );
//  nh.spinOnce();
  delay(2000);

  //pH code 
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
  Serial.write((char*)(&phValue), sizeof(float));
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  delay(800);
  digitalWrite(13, LOW); 
  //publish pH
  str_msg.data = phValue;
  chatter.publish( &str_msg );
  nh.spinOnce();

}
