#ifndef __hsvtorgb
#define __hsvtorgb

#include <Arduino.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

rgb_t HSVtoRGB(int h, double s, double v);

#endif