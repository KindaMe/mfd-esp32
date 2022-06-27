#include <Arduino.h>
#include <WiFi.h>
#include "AsyncUDP.h"
#include "WiFiManager.h"

class WiFiConnection
{
private:
    WiFiManager wm;

public:
    void Init()
    {
        // String hostname = "ESP32_1";
        // WiFi.setHostname(hostname.c_str());
        WiFi.mode(WIFI_STA);

        bool res;
        res = wm.autoConnect("MFD Config", "password");
        if (!res)
        {
            Serial.println("Connection Error");
            // ESP.restart();
        }
        else
        {
            Serial.println("Connected!");
        }
    }

    void ResetSettings()
    {
        wm.resetSettings();
    }

} _WiFiConnection;