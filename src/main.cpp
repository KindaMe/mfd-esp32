#include "Network.h"
#include "MFD.h"
#include "UDP_Listener.h"

const int WiFiResetButton = 13;

void setup()
{
  Serial.begin(115200);

  pinMode(WiFiResetButton, INPUT_PULLUP);

  _DisplayData.Init();

  _WiFiConnection.Init();

  _DisplayData.WelcomeLed();

  _UPD_Listener.Init();
}

void loop()
{
  if (digitalRead(WiFiResetButton) == 0)
  {
    _WiFiConnection.ResetSettings();
    ESP.restart();
  }

  if (TimerResetRecently == false)
  {
    _DisplayData.UpdateMFD();

    if (millis() - Timer > TimerInterval)
    {
      _DisplayData.Reset();
      TimerResetRecently = true;
    }
  }
}
