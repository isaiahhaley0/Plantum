#include "CamLib.hpp"
#include <Arduino.h>
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <EEPROM.h>   
#include "esp_camera.h"


CamLib::CamLib(/* args */)
{
        pinMode(FlashPin, OUTPUT);

}

CamLib::~CamLib()
{
}

void CamLib::Setup()
{

           WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
       config_cam();
         mount_card();
}

void CamLib::TurnOnFlash()
{
    pinMode(FlashPin,OUTPUT);
}

void CamLib::TurnOffFlash()
{
    digitalWrite(FlashPin,INPUT);
}

void CamLib::config_cam()
{
      config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  config.grab_mode = CAMERA_GRAB_LATEST;
    if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
    esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void CamLib::mount_card()
{
    
     if(!SD_MMC.begin()){
    Serial.println("SD Card Mount Failed");
    return;
  }
  
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD Card attached");
    return;
  }
}

void CamLib::take_photo()
{
    camera_fb_t * fb =  esp_camera_fb_get();  
if(!fb) {
  Serial.println("Camera capture failed");
  return;
}
    EEPROM.begin(EEPROM_SIZE);
pictureNumber = EEPROM.read(0) + 1;
String path = "/picture" + String(pictureNumber) +".jpg";

//save

fs::FS &fs = SD_MMC; 
Serial.printf("Picture file name: %s\n", path.c_str());

File file = fs.open(path.c_str(), FILE_WRITE);
if(!file){
  Serial.println("Failed to open file in writing mode");
} 
else {
  file.write(fb->buf, fb->len); // payload (image), payload length
  Serial.printf("Saved file to path: %s\n", path.c_str());
  EEPROM.write(0, pictureNumber);
  EEPROM.commit();
}
file.close();
api.sendImage(path.c_str(),fb);
esp_camera_fb_return(fb); 
}
