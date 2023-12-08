#ifndef CONTROLLERMODE_h
#define CONTROLLERMODE_h

#include "Arduino.h"
#include "Joint.h" 

class ControllerMode
{
    public:
        ControllerMode(int id);
        int GetId();
        virtual void GetJointAngle(float deltaA, float deltaB, float deltaC, float deltaD, float *thetaBase, float *thetaShoulder, float *thetaElbow, float *thetaGripper) = 0;
    protected:
        float MapFloat(float x, float in_min, float in_max, float out_min, float out_max);
        int id;
        int tempValue;
};

class ControllerModePotVal : public ControllerMode
{
    public:
        ControllerModePotVal(int id);
        virtual void GetJointAngle(float deltaA, float deltaB, float deltaC, float deltaD, float *thetaBase, float *thetaShoulder, float *thetaElbow, float *thetaGripper);
    protected:
};

class ControllerModePotMove : public ControllerMode
{
    public:
        ControllerModePotMove(int id);
        virtual void GetJointAngle(float deltaA, float deltaB, float deltaC, float deltaD, float *thetaBase, float *thetaShoulder, float *thetaElbow, float *thetaGripper);
    protected:
};

#endif