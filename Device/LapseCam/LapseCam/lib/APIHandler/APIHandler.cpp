#include "APIHandler.hpp"
#include <HTTPClient.h>
#include <WiFi.h>
#include "esp_camera.h"
#include <ArduinoJson.h>

using namespace std;

void APIHandler::initWifi()
{
          WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());

}

APIHandler::APIHandler(/* args */)
{
    
      
}

APIHandler::~APIHandler()
{
}

void APIHandler::sendImage(string filepath,camera_fb_t* fb)
{
    if(!WiFi.isConnected())
    {
        initWifi();
    }
    string path = basePath+"/upload?name=cam1";
    client.begin(path.c_str());
    string fmData = "form-data; name=\"img\"; filename="+filepath;
    client.addHeader("Content-Disposition",fmData.c_str());
     client.addHeader("Content-Type", "image/jpeg");
 int httpResponseCode = client.POST(fb->buf, fb->len);
client.end();
}

bool APIHandler::check_flash()
{
      if(!WiFi.isConnected())
    {
        initWifi();
    }
    string path = basePath+"/camera";
    client.begin(path.c_str());
    int cd = client.GET();
if(cd ==  200)
{
    string payload = client.getString().c_str();
    JsonDocument doc;
    deserializeJson(doc,payload);
    return doc["flash"];
}
client.end();
return true;

}
