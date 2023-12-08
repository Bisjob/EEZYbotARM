#include "Controllers/Controller.h"

Controller::Controller(InputAxis* lx, InputAxis* ly, InputAxis* rx, InputAxis* ry, Joint* j1, Joint* j2, Joint* j3, Joint* j4)
    :PotValMode(0), PotMoveMode(1)
{
    this->lx = lx;
    this->ly = ly;
    this->rx = rx;
    this->ry = ry;

    this->j1 = j1;
    this->j2 = j2;
    this->j3 = j3;
    this->j4 = j4;
    curMode = &PotMoveMode;
}

void Controller::Init()
{
    rx->Init();
    ry->Init();
    lx->Init();
    ly->Init();

    j1->Init();
    delay(500);

    j2->Init();
    delay(500);

    j3->Init();
    delay(500);

    j4->Init();
    delay(500);
}

void Controller::SetSpeed(double speedPercent)
{
    j1->SetSpeed(speedPercent);
    j2->SetSpeed(speedPercent);
    j3->SetSpeed(speedPercent);
    j4->SetSpeed(speedPercent);
}

void Controller::ReadInputs()
{
    // read joysticks inputs
    float lxVal = lx->Read();
    float lyVal = ly->Read();
    float rxVal = rx->Read();
    float ryVal = ry->Read();

    // readu current joints angles
    float a1 = j1->GetCurPos();
    float a2 = j2->GetCurPos();
    float a3 = j3->GetCurPos();
    float a4 = j4->GetCurPos();

    // obtain the new joints angles
    curMode->GetJointAngle(lxVal, lyVal, rxVal, ryVal, &a1, &a2, &a3, &a4);

    // set the angles
    j1->SetAimedPos(a1);
    j2->SetAimedPos(a2);
    j3->SetAimedPos(a3);
    j4->SetAimedPos(a4);

    Serial.print("J1: ");
    Serial.print(j1->GetCurPos());
    Serial.print(" (");
    Serial.print(a1);
    Serial.print(") ");
    Serial.print(" (speed: ");
    Serial.print(j1->GetSpeed());
    Serial.print(") i:");
    Serial.print(lxVal);
    
    Serial.print("  J2: ");
    Serial.print(j2->GetCurPos());
    Serial.print(" (");
    Serial.print(a2);
    Serial.print(") ");
    Serial.print(" (speed: ");
    Serial.print(j2->GetSpeed());
    Serial.print(") i:");
    Serial.print(lyVal);
    
    Serial.print("  J3: ");
    Serial.print(j3->GetCurPos());
    Serial.print(" (");
    Serial.print(a3);
    Serial.print(") ");
    Serial.print(" (speed: ");
    Serial.print(j3->GetSpeed());
    Serial.print(") i:");
    Serial.print(rxVal);
    
    Serial.print("  J4: ");
    Serial.print(j4->GetCurPos());
    Serial.print(" (");
    Serial.print(a4);
    Serial.print(")");
    Serial.print(" (speed: ");
    Serial.print(j4->GetSpeed());
    Serial.print(") i:");
    Serial.print(ryVal);

    Serial.println("");
}

void Controller::IncrMode()
{
    ++curModeId;
    if (curModeId == 2)
        curModeId = 0;
    switch (curModeId)
    {
    case 0:
        curMode = &PotValMode;
        break;
        
    case 1:
        curMode = &PotMoveMode;
        break;
        
    default:
        break;
    }
}


ControllerMode* Controller::GetCurMode()
{
    return curMode;
}

int Controller::GetCurModeId()
{
    return curModeId;
}

void Controller::DoWork()
{
    j1->DoWork();
    j2->DoWork();
    j3->DoWork();
    j4->DoWork();
}