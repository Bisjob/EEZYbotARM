
#ifndef H_JOINT
#define H_JOINT

#include "Servo.h"

class Joint
{
    public:
        Joint(int pin, int minPos, int maxPos, double minSpeed, double maxSpeed);
        void Init();
        void GoTo(int pos);
        void DoWork();
        void SetAimedPos(int newPos);
        int GetCurPos();
        int GetAimedPos();
        double GetSpeed();
        void SetSpeed(double speedPercent);

    private:
        Servo servo;
        int minPos;
        int maxPos;
        int pin;
        int curPos;
        int aimedPos;
        double minSpeed;
        double maxSpeed;
        double speed; // degree per ms
        double integral;
        double prevError;
        unsigned long lastMoveTime;
};

#endif //H_JOINT