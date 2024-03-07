#include <Arduino.h>
#include "WifiManager.h"
#include <Wire.h>  
#define lightpin 39
// put function declarations here:
int myFunction(int, int);
double getReading();

WifiManager wm;

void setup() {
  // put your setup code here, to run once:
 
 pinMode(lightpin,INPUT);
  Serial.begin(115200);
  wm.initWiFi();


}

void loop() {
  // put your main code here, to run repeatedly:
  wm.recordLight(getReading());
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

double getReading()
{
  
  double sum = 0;
  int readingCount = 100;
  for(int i = 0; i < readingCount; i++)
  {
    double reading = analogRead(lightpin);
    Serial.println(reading);
    sum += reading;
    delay(10);
  }
  return sum/(double)readingCount ;

}

