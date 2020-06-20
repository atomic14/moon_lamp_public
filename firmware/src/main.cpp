#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ota.h"
#include "ledcontrol.h"
#include "webcontrol.h"
#include "papertrail.h"

const char *ssid = "<YOUR_SSID>";
const char *password = "<YOUR_PASSWORD>";

unsigned long lastTime = 0;
OTA *ota = NULL;
LEDControl *ledControl = NULL;
WebControl *webControl = NULL;
Papertrail *papertrail = NULL;

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  papertrail = new Papertrail("Moon_Lamp", "logs5.papertrailapp.com", 34663);
  papertrail->log("Started up");
  ota = new OTA(papertrail, "moonlamp");
  ledControl = new LEDControl(papertrail);
  webControl = new WebControl(papertrail, ledControl);
  lastTime = millis();
}

void loop()
{
  unsigned long current = millis();
  unsigned long elapsed = current - lastTime;
  lastTime = current;
  ota->loop();
  ledControl->loop(elapsed);
}
