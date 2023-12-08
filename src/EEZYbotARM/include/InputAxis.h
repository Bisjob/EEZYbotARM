#ifndef H_INPUTAXIS
#define H_INPUTAXIS

class InputAxis
{
    public:
        InputAxis(int pin, bool invert);
        void Init();
        float Read();

    private:
        int pin;
        bool invert;
        int midValue;
        float MapFloat(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif //H_JOINT