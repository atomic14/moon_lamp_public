#include <Arduino.h>
#include <cmath>
#include "hsvtorgb.h"

rgb_t HSVtoRGB(int h, double s, double v)
{
    double c = s * v;
    double x = c * (1 - std::abs(fmod(h / 60.0, 2) - 1));
    double m = v - c;
    double r, g, b;

    if (h >= 0 && h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (h >= 60 && h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (h >= 120 && h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (h >= 180 && h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (h >= 240 && h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    rgb_t result = {
        uint8_t((r + m) * 255.0),
        uint8_t((g + m) * 255.0),
        uint8_t((b + m) * 255.0)};
    return result;
}
