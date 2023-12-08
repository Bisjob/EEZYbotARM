#include <Led.h>
#include <Arduino.h>

Led Led::LEDS[TOTAL_LED_COUNT] = 
{
    Led(10),
};

Led::Led(int pin)
{
    this->pin = pin;
    this->ledState = false;
    pinMode(pin, OUTPUT);
}

int Led::GetPin()
{
    return pin;
}

void Led::SetState(bool state)
{
    this->ledState = state;
}

bool Led::GetState()
{
    return ledState;
}

void Led::ChangePeriodBlink(int period)
{
    this->blinkPeriod = period;
}
void Led::StartBlink(int period, int duration)
{
    blinkActivated = true;
    blinkPeriod = period;
    blinkDuration = duration;

    infinitBlink = false;
    ledState = true;
    blinkStart = millis();
    blinkStartPeriod = millis();
}

void Led::StopBlink()
{
    blinkActivated = false;
    ledState = false;
}

bool Led::IsBlinking()
{
    return blinkActivated;
}

void Led::DoJob()
{
    if (blinkActivated)
    {
        if (blinkDuration != 0 && millis() - blinkStart >= blinkDuration)
        {  
            blinkActivated = false;
            StopBlink();
        }
        else if (millis() - blinkStartPeriod >= blinkPeriod)
        {
            ledState = !ledState;
            blinkStartPeriod = millis();
        }
    }

    if (ledState != lastLedState)
    {
        digitalWrite(pin, ledState);
    }
    lastLedState = ledState;
}