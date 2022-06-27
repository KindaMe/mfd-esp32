#include <Arduino.h>
#ifndef MFD
#define MFD

class Parser
{
private:
  struct DataRecieved
  {
    uint16_t Speed;
    int8_t Gear;
    uint16_t RevLights;
  };

public:
  void Parse(byte (&packet)[1500])
  {
    DataRecieved *RecievedData = reinterpret_cast<DataRecieved *>(packet);

    _DisplayData.speed = RecievedData->Speed;
    _DisplayData.gear = RecievedData->Gear;
    _DisplayData.revlights[0] = RecievedData->RevLights;
    _DisplayData.revlights[1] = RecievedData->RevLights >> 8;
  }
} _Parser_DRIVER;

#endif