#include "InputAxis.h"
#include "Arduino.h"

#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 1023

InputAxis::InputAxis(int pin, bool invert)
:pin(pin), invert(invert)
{

}

void InputAxis::Init()
{
    const int cnt = 10;
    int sum = 0;
    for (int i = 0; i < cnt; ++i)
    {
        sum += analogRead(pin);
    }

    this->midValue = (float)sum / (float)cnt;
}

float InputAxis::Read()
{
    int val = analogRead(pin);
    if (val == midValue) 
        return 0;

    float result;
    // If inputValue is less than midValue, map between [0, midValue] to [0, -1]
    if (val < midValue) 
    {
        result = MapFloat(val, 0, midValue, -1, 0);
    } 
    // Otherwise, map between [midValue, 1023] to [0, 1]
    else 
    {
        result =MapFloat(val, midValue, 1023, 0, 1);
    }
    if (invert)
        result *= -1;
    return result;
}

float InputAxis::MapFloat(float x, float in_min, float in_max, float out_min, float out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}