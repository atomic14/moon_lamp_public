class Papertrail;

class OTA
{
    Papertrail *papertrail;

public:
    OTA(Papertrail *papertrail, const char *hostname);
    void loop();
};
