#include <string>
#include <HTTPClient.h>
#include <esp_camera.h>

#pragma once

using namespace std;
class APIHandler
{
private:
    /* data */
    string ssid = "CenturyLink3333";
    string password = "c8m4i5w7b2t3s6";
    string basePath = "http://192.168.0.47:5000";
    HTTPClient client;
    
public:
    APIHandler(/* args */);
    ~APIHandler();
void initWifi();
    void sendImage(string filepath,camera_fb_t* fb, int image_num);
    bool check_flash();



};






