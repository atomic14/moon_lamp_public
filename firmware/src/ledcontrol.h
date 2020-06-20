#include "hsvtorgb.h"

class Papertrail;

class LEDControl
{
private:
    Papertrail *papertrail;
    bool cycle;
    bool indicator;
    float hueCycle;
    unsigned int lastUpdate;
    rgb_t rgb;

public:
    LEDControl(Papertrail *papertrail);
    void setRGB(rgb_t rgb);
    rgb_t getRGB()
    {
        return rgb;
    }
    void setIndicator(bool on);
    bool getIndicator()
    {
        return indicator;
    }
    void setCycle(bool on);
    bool getCycle()
    {
        return cycle;
    }
    void loop(unsigned int elapsedMs);
};
