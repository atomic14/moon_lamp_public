#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ota.h"
#include "papertrail.h"

OTA::OTA(Papertrail *papertrail, const char *hostname)
{
    this->papertrail = papertrail;
    ArduinoOTA.setHostname(hostname);
    ArduinoOTA
        .onStart([this]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            this->papertrail->log("Start updating " + type);
        })
        .onEnd([this]() {
            this->papertrail->log("Update Complete");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            unsigned int percent = progress / (total / 100);
            digitalWrite(25, (percent % 2) == 1 ? HIGH : LOW);
            // Serial.printf("Progress: %u%%\r", percent);
        })
        .onError([this](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                this->papertrail->log("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                this->papertrail->log("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                this->papertrail->log("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                this->papertrail->log("Receive Failed");
            else if (error == OTA_END_ERROR)
                this->papertrail->log("End Failed");
        });
    ArduinoOTA.begin();
}

void OTA::loop()
{
    ArduinoOTA.handle();
}