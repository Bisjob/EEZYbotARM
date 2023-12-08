#include "Controllers/ControllerMode.h"


#define JOINT_MIN 0
#define JOINT_MAX 180

#define BASE_HEIGHT 20
#define SHOULDER_LENGTH 20
#define ELBOW_LENGTH 20
#define GRIPPER_LENGTH 5

ControllerMode::ControllerMode(int id)
    : id(id)
{
}

int ControllerMode::GetId()
{
    return id;
}

float ControllerMode::MapFloat(float x, float in_min, float in_max, float out_min, float out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


ControllerModePotVal::ControllerModePotVal(int id)
    : ControllerMode(id)
{
}

void ControllerModePotVal::GetJointAngle(float deltaA, float deltaB, float deltaC, float deltaD, float *thetaBase, float *thetaShoulder, float *thetaElbow, float *thetaGripper)
{
    if(thetaBase == nullptr || thetaShoulder == nullptr || thetaElbow == nullptr || thetaGripper == nullptr) 
        return;

    *thetaBase = MapFloat(deltaA, -1., 1., JOINT_MIN, JOINT_MAX);
    *thetaShoulder = MapFloat(deltaB, -1., 1., JOINT_MIN, JOINT_MAX);
    *thetaElbow = MapFloat(deltaC, -1., 1., JOINT_MIN, JOINT_MAX);
    *thetaGripper = MapFloat(deltaD, -1., 1., JOINT_MIN, JOINT_MAX);
}



ControllerModePotMove::ControllerModePotMove(int id)
    : ControllerMode(id)
{
}

void ControllerModePotMove::GetJointAngle(float deltaA, float deltaB, float deltaC, float deltaD, float *thetaBase, float *thetaShoulder, float *thetaElbow, float *thetaGripper)
{
    if(thetaBase == nullptr || thetaShoulder == nullptr || thetaElbow == nullptr || thetaGripper == nullptr) 
        return;

    float change1 = abs(deltaA) >= 0.5 ? deltaA * 10 : 0;
    float change2 = abs(deltaB) >= 0.5 ? deltaB * 10 : 0;
    float change3 = abs(deltaC) >= 0.5 ? deltaC * 10 : 0;
    float change4 = abs(deltaD) >= 0.5 ? deltaD * 10 : 0;

    *thetaBase = *thetaBase + change1;
    *thetaShoulder = *thetaShoulder + change2;
    *thetaElbow = *thetaElbow + change3;
    *thetaGripper = *thetaGripper + change4;
}