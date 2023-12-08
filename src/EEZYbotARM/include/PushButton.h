#ifndef PushButton_h
#define PushButton_h

const static int DEBOUNCE_DELAY = 50;

class PushButton 
{
    public:
        PushButton(int pin);
        bool CheckChanges();
        int GetCurrentState();

    private:
        unsigned long lastDebounceTime;
        int currentState;
        int lastState;
        int pin;
};

#endif