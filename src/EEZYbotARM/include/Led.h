#ifndef Led_h
    #define Led_h

    #define TOTAL_LED_COUNT 1

    class Led
    {
        public:
            Led(int pin);
            int GetPin();
            void SetState(bool state);
            bool GetState();
            void StartBlink(int period, int duration);
            void ChangePeriodBlink(int period);
            void StopBlink();
            bool IsBlinking();
            void DoJob();
            static Led LEDS[];
        private:
            int pin;
            bool ledState;
            bool lastLedState;
            bool blinkActivated;
            int blinkPeriod;
            int blinkDuration;
            bool infinitBlink;
            unsigned long blinkStart;
            unsigned long blinkStartPeriod;
    };

#endif