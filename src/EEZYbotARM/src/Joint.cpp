#include "Joint.h"
#include "Arduino.h"

Joint::Joint(int pin, int minPos, int maxPos, double minSpeed, double maxSpeed)
    :pin(pin), minPos(minPos), maxPos(maxPos), minSpeed(minSpeed), maxSpeed(maxSpeed), integral(0), prevError(0)
{
}

void Joint::Init()
{
    servo.attach(pin, minPos, maxPos);
    GoTo((minPos + maxPos) / 2);
}

 void Joint::GoTo(int pos)
 {
     this->aimedPos = pos;
     servo.write(pos);
     this->curPos = pos;
 }

void Joint::SetAimedPos(int newPos)
{
    this->aimedPos = newPos;
}

int Joint::GetCurPos()
{
    return this->curPos;
}

int Joint::GetAimedPos()
{
    return this->aimedPos;
}
void Joint::SetSpeed(double speedPercent)
{
    this->speed = minSpeed + (speedPercent * (maxSpeed - minSpeed));
}
double Joint::GetSpeed()
{
    return this->speed;
}

void Joint::DoWork()
{
    double kp = 1;    // Proportional constant
    double ki = 0;  // Integral constant
    double kd = 0;   // Derivative constant

    // Calculate elapsed time
    unsigned long currentTime = millis();
    float elapsedTime = (currentTime - lastMoveTime);

    double error = aimedPos - curPos;
    if (abs(error) < 1)
        return;

    integral += error * elapsedTime;
    double derivative = (error - prevError) / elapsedTime;
    double output = kp * error + ki * integral + kd * derivative;
    float maxMovement = speed * elapsedTime;

    if (output > 0)
        output = min(output, maxMovement);
    else
        output = max(output, -maxMovement);

    curPos += output;
    curPos = constrain(curPos, minPos, maxPos);

    servo.write(curPos);

    prevError = error;
    lastMoveTime = currentTime;
}