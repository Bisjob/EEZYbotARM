/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo servoR;  
Servo servoX;  
Servo servoY;  
Servo servoG;  


const int btnpin = 12;
const int potpin = A0;  // analog pin used to connect the potentiometer

int potval;    // variable to read the value from the analog pin

int lastbBtnState = HIGH; // the previous state from the input pin
int currentBtnState;    // the current reading from the input pin
int servoCase = 0;

void setup() {
  pinMode(btnpin, INPUT_PULLUP);
  servoR.attach(2); 
  servoX.attach(3); 
  servoY.attach(4); 
  servoG.attach(5); 
    Serial.begin(9600);
}

void loop() {
  currentBtnState = digitalRead(btnpin);
  if(lastbBtnState == LOW && currentBtnState == HIGH)
  {
    servoCase++; 
    if (servoCase == 4)
      servoCase = 0;
    Serial.print("Selection changed to");
    Serial.println(servoCase);
  }
  
  potval = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  potval = map(potval, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)

  switch (servoCase)
  {
    case 0:
      servoR.write(potval);
      break;
    case 1:
      servoX.write(potval);
      break;
    case 2:
      servoY.write(potval);
      break;
    case 3:
      servoG.write(potval);
      break;
  }
  lastbBtnState = currentBtnState;
  
                    // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
