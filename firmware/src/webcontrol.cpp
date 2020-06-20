#include <FS.h>
#include "SPIFFS.h"
#include "ledcontrol.h"
#include "webcontrol.h"
#include "papertrail.h"
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include <ArduinoJson.h>

AsyncWebServer server(80);

WebControl::WebControl(Papertrail *_papertrail, LEDControl *_ledControl) : papertrail(_papertrail), ledControl(_ledControl)
{
    SPIFFS.begin();

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, PUT");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

    server.addHandler(new AsyncCallbackJsonWebHandler("/rgb", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        const JsonObject &jsonObj = json.as<JsonObject>();
        this->ledControl->setRGB({jsonObj["red"], jsonObj["green"], jsonObj["blue"]});
        request->send(200, "OK");
    }));

    server.addHandler(new AsyncCallbackJsonWebHandler("/led", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        const JsonObject &jsonObj = json.as<JsonObject>();
        this->ledControl->setIndicator(jsonObj["on"]);
        request->send(200, "OK");
    }));

    server.addHandler(new AsyncCallbackJsonWebHandler("/cycle", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        const JsonObject &jsonObj = json.as<JsonObject>();
        this->ledControl->setCycle(jsonObj["on"]);
        request->send(200, "OK");
    }));

    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        rgb_t current = ledControl->getRGB();
        char buffer[200];
        sprintf(buffer,
                "{ \"red\": %d, \"green\": %d, \"blue\": %d, \"cycle\": %s, \"indicator\": %s }",
                current.r, current.g, current.b,
                ledControl->getCycle() ? "true" : "false",
                ledControl->getIndicator() ? "true" : "false");
        request->send(200, "application/json", buffer);
    });

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", String("Bob Banana").c_str());
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        if (request->method() == HTTP_OPTIONS)
        {
            request->send(200);
        }
        else
        {
            request->send(404);
        }
    });
    server.begin();
}
