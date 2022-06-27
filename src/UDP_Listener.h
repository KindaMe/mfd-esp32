#include <Arduino.h>
#include <WiFi.h>
#include "AsyncUDP.h"
#include "Parsers.h"

#define UDP_PORT 21377

AsyncUDP udp;

byte packet[1500];

int Timer;
int TimerInterval = 333;
bool TimerResetRecently = false;

class UPD_Listener
{
public:
    void Init()
    {
        Timer = millis();

        if (udp.listen(UDP_PORT))
        {
            Serial.println("UDP - ENABLED");

            udp.onPacket([](AsyncUDPPacket asyncPacket)
                         {
                                    asyncPacket.read(packet, 1500);
                                    _Parser_DRIVER.Parse(packet);
                                    Serial.println("PACKET - RECIEVED");
                                   
                                    TimerResetRecently = false;
                                    Timer = millis(); });
        }
        else
        {
            Serial.println("PACKET - ERROR");
        }
    }
} _UPD_Listener;
