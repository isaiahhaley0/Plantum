#include <WiFi.h>
#include <HTTPClient.h>

#pragma once

class WifiManager
{
private:
const char* ssid = "CenturyLink3333";
const char* password = "c8m4i5w7b2t3s6";
const char* server = "http://192.168.0.5:5000";
HTTPClient client;
public:
    WifiManager(/* args */);
    ~WifiManager();
    void initWiFi(); 
    void recordLight(double reading);
    void startClient(char* serv);

};


