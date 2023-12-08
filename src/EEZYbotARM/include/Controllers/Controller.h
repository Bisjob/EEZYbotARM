#ifndef CONTROLLER_h
#define CONTROLLER_h

#include "Arduino.h"
#include "Joint.h" 
#include "ControllerMode.h"
#include "InputAxis.h"

class Controller
{
    public:
        Controller(InputAxis* lx, InputAxis* ly, InputAxis* rx, InputAxis* ry, Joint* j1, Joint* j2, Joint* j3, Joint* j4);
        ControllerModePotVal PotValMode;
        ControllerModePotMove PotMoveMode;
        void Init();
        int GetId();
        void ReadInputs();
        void IncrMode();
        ControllerMode* GetCurMode();
        int GetCurModeId();
        void DoWork();
        void SetSpeed(double speedPercent);
    private:
        Joint* j1;
        Joint* j2;
        Joint* j3;
        Joint* j4;
        InputAxis* lx;
        InputAxis* ly;
        InputAxis* rx;
        InputAxis* ry;
        ControllerMode* curMode;
        int curModeId;
};


#endif