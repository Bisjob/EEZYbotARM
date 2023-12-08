#include <Arduino.h>
#include <InverseK.h>
#include <Joint.h>
#include <Led.h>
#include <Controllers/Controller.h>
#include <PushButton.h>

/*****************************************
 *            Inputs pin
 * **************************************/
// const int ledgreenpin = 10;
const int ledRedpin = 9;

// const int btnSpeedPin = 7;
// const int btnModePin = 8;

const int RXpin = A1;
const int RYpin = A0;
const int LXpin = A2;
const int LYpin = A3;

const int SpeedPotPin = A7;

const int j1Pin = 2;
const int j2Pin = 3;
const int j3Pin = 4;
const int j4Pin = 5;


/******************************************
 *            Working objects
 * **************************************/
Joint jointR(j1Pin, 0, 180, 0.02, 0.100);
Joint jointX(j2Pin, 20, 160, 0.03, 0.110);
Joint jointY(j3Pin, 20, 160, 0.03, 0.110);
Joint jointG(j4Pin, 0, 180, 0.03, 0.120);

InputAxis lx(RXpin, false);
InputAxis ly(RYpin, false);
InputAxis rx(LXpin, true);
InputAxis ry(LYpin, false);

Controller controller(&lx, &ly, &rx, &ry, &jointR, &jointX, &jointY, &jointG);

// PushButton btnSpeed(btnSpeedPin);
// PushButton btnMode(btnModePin);

// Led greenLed(ledgreenpin);
Led redLed(ledRedpin);

// speed => blink conversion
const int speedBlinkMaxPeriod = 1000;
const int speedBlinkdecrement = speedBlinkMaxPeriod - 100;
float speedBlinkPeriod = 0;

float MapFloat(float x, float in_min, float in_max, float out_min, float out_max) 
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Start Init");

  redLed.SetState(false);
  redLed.DoJob();

  controller.SetSpeed(0.1);
  controller.Init();

  redLed.SetState(true);
  redLed.DoJob();

  Serial.println("Let's go");
}

void loop()
{
    // if (btnSpeed.CheckChanges())
    // {
    //   speed = controller.GetSpeed();
    //   speed = speed += speedInc;
    //   if (speed > speedMax)
    //     speed = 1;

    //   controller.SetSpeed(speed);
      
    //   Serial.print("Speed changed to ");
    //   Serial.println(speed);
    // }

    // if (btnMode.CheckChanges())
    // {
    //     controller.IncrMode();
        
    //     Serial.print("Mode changed to ");
    //     Serial.println(controller.GetCurModeId());

    //     if (controller.GetCurModeId() == 0)
    //     {
    //         yellowLed.SetState(false);
    //         greenLed.SetState(true);
    //     }
    //     else
    //     {
    //         yellowLed.SetState(true);
    //         greenLed.SetState(false);
    //     }
    // }

  int speedValue = analogRead(SpeedPotPin);
  double speedPercent = MapFloat(speedValue, 0., 1023, 0., 1.);
  speedBlinkPeriod = MapFloat(speedPercent, 0., 1., 0., speedBlinkMaxPeriod);
  

  // Serial.print("speedValue ");
  // Serial.print(speedValue);
  // Serial.print("  speed ");
  // Serial.print(speed);
  // Serial.print("  speedBlinkPeriod ");
  // Serial.println(speedBlinkPeriod);

  controller.SetSpeed(speedPercent);

  controller.ReadInputs();
  controller.DoWork();
  redLed.DoJob();
}
