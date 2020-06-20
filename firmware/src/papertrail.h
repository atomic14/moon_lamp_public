#include <Arduino.h>

class WiFiUDP;

class Papertrail
{
private:
    String systemName;
    String host;
    int port;
    WiFiUDP *wifiUdp;

public:
    Papertrail(String systemName, String host, int port);
    size_t log(String msg);
};
