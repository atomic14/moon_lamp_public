#include "Arduino.h"
#include "ledcontrol.h"
#include "papertrail.h"
#include "hsvtorgb.h"

// the number of the LED pin
// const int red = 18;
// const int green = 19;
// const int blue = 21;

const int red = 27;
const int green = 33;
const int blue = 32;

// setting PWM properties
const int freq = 100000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;

LEDControl::LEDControl(Papertrail *papertrail)
{
    this->papertrail = papertrail;
    pinMode(25, OUTPUT);

    // configure LED PWM functionalitites
    ledcSetup(redChannel, freq, resolution);
    ledcSetup(greenChannel, freq, resolution);
    ledcSetup(blueChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(red, redChannel);
    ledcAttachPin(green, greenChannel);
    ledcAttachPin(blue, blueChannel);

    pinMode(red, OUTPUT_OPEN_DRAIN);
    pinMode(green, OUTPUT_OPEN_DRAIN);
    pinMode(blue, OUTPUT_OPEN_DRAIN);

    ledcWrite(redChannel, 0);
    ledcWrite(greenChannel, 0);
    ledcWrite(blueChannel, 0);

    cycle = false;
    hueCycle = 0;
    indicator = 0;
    rgb = {0, 0, 0};
}

void LEDControl::setRGB(rgb_t rgb)
{
    ledcWrite(redChannel, rgb.r);
    ledcWrite(greenChannel, rgb.g);
    ledcWrite(blueChannel, rgb.b);
    this->rgb = rgb;
}

void LEDControl::setIndicator(bool on)
{
    digitalWrite(2, on ? HIGH : LOW);
}

void LEDControl::setCycle(bool on)
{
    this->cycle = on;
    rgb_t rgb = HSVtoRGB(hueCycle, 1.0, 1.0);
    this->setRGB(rgb);
}

void LEDControl::loop(unsigned int elapsedMs)
{
    if (this->cycle)
    {
        hueCycle += elapsedMs * 3 / 1000.0;
        while (hueCycle > 360)
        {
            hueCycle -= 360;
        }
        lastUpdate += elapsedMs;
        if (lastUpdate > 500)
        {
            lastUpdate = 0;
            rgb_t rgb = HSVtoRGB(hueCycle, 1.0, 1.0);
            // char buf[100];
            // sprintf(buf, "Cyclng to %d %d %d", rgb.r, rgb.g, rgb.b);
            // this->papertrail->log(buf);
            this->setRGB(rgb);
        }
    }
}