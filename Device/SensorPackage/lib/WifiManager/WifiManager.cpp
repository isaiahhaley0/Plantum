#include "WifiManager.h"
#include <string>
WifiManager::WifiManager(/* args */)
{
}

WifiManager::~WifiManager()
{
}

void WifiManager::initWiFi()
{
      WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void WifiManager::recordLight(double reading)
{
    char* light = "http://192.168.0.5:5000/light";
    String jsn = "{\"light\": " + (String)reading+"}";
    startClient(light);
    client.PUT(jsn);
}

void WifiManager::startClient(char* serv)
{
    client.begin(serv);
    client.addHeader("Content-Type", "application/json"); 

}
