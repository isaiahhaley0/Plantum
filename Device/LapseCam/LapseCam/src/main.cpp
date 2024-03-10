#include <Arduino.h>
#include "CamLib.hpp"

CamLib* cl;
u_long last = 0;
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5 
int photos_since_restart =0;
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}



void setup() { 
  
   Serial.begin(115200);
    // Serial.setDebugOutput(true);
  cl = new CamLib();
print_wakeup_reason();
esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
     cl->Setup();
  Serial.println();
   Serial.print("Taking photo");
 
cl->take_photo();
last = millis();
 
  Serial.print("Done");


}

void loop() {
  if(millis() > last + 60000)
  {
   
  cl->take_photo();
 last = millis();
 if(photos_since_restart > 60)
 {
  Serial.flush(); 
  cl->~CamLib();
  esp_deep_sleep_start();
 }
 else
 {
  photos_since_restart++;
 }
 
  }
}

 