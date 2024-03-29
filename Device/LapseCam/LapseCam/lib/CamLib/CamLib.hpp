#include <Arduino.h>
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <EEPROM.h>   
#include "esp_camera.h"
#include "APIHandler.hpp"
#pragma once
#define CAMERA_MODEL_AI_THINKER
#define EEPROM_SIZE 1

// Pin definition for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22




class CamLib
{
private:
    /* data */
    int FlashPin =  4;
    int pictureNumber = 0;
      camera_config_t config;
      APIHandler api;
      int image_count = 0;
public:
    CamLib(/* args */);
    ~CamLib();
    void Setup();
    void TurnOnFlash();
    void TurnOffFlash();
    void config_cam();
    void mount_card();
    void take_photo();

};
 