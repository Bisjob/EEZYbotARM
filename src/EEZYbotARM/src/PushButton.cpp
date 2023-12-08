#include "Arduino.h"
#include "PushButton.h"

PushButton::PushButton(int pin)
{
    this->pin = pin;
    lastDebounceTime = millis();
    pinMode(pin, INPUT_PULLUP);
    currentState = digitalRead(pin);
    lastState = currentState;
}

int PushButton::GetCurrentState()
{
    return currentState;
}

bool PushButton::CheckChanges()
{
    int reading = digitalRead(pin);
  // If the switch changed, due to noise or pressing:
  if (reading != lastState) 
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) 
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != currentState) 
    {
      currentState = reading;
    
        // only toggle the LED if the new button state is HIGH
        if (currentState == HIGH) 
        {
            lastState = reading;
            return true;
        }
    }
  }

    // save the reading. Next time through the loop, it'll be the lastbtnChronoState:
    lastState = reading;
    return false;
}