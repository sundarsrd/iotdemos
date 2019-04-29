#include "MQ135.h"
#define ANALOGPIN A0

MQ135 gasSensor = MQ135(ANALOGPIN);
void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  float rzero = gasSensor.getRZero(); //this to get the rzero value, uncomment this to get ppm value
 float ppm = gasSensor.getPPM(); // this to get ppm value, uncomment this to get rzero value
 Serial.println(rzero); // this to display the rzero value continuously, uncomment this to get ppm value
 Serial.println(ppm); // 
 float air_quality=((100-0)/(ppm-0))*(ppm-0)+0;
  Serial.println(air_quality);
  
  delay(1000);
}
