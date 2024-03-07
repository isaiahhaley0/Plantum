#include <Arduino.h>
#include "CamLib.hpp"
  CamLib cl;

u_long last = 0;
void setup() {
  // put your setup code here, to run once:

   Serial.begin(115200);
    // Serial.setDebugOutput(true);
     cl.Setup();
  Serial.println();
   Serial.print("Taking photo");
 
cl.take_photo();
last = millis();
 
  Serial.print("Done");

}

void loop() {
  if(millis() > last + 60000)
  {
   
  cl.take_photo();
  last = millis();
 
  }
}

 