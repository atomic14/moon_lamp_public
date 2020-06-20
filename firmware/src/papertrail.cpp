#include <WiFiUdp.h>
#include "papertrail.h"

Papertrail::Papertrail(String systemName, String host, int port)
{
    this->host = host;
    this->systemName = systemName;
    this->port = port;
    this->port = port;
    this->wifiUdp = new WiFiUDP();
}

size_t Papertrail::log(String msg)
{
    size_t result = Serial.println(msg);
    String logStr = "<22>" + this->systemName + ": " + String(msg);
    wifiUdp->beginPacket(this->host.c_str(), this->port);
    wifiUdp->write((const uint8_t *)logStr.c_str(), logStr.length());
    wifiUdp->endPacket();
    return result;
}
