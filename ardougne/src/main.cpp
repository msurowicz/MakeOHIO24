#include <Arduino.h>

#define VRX_PIN A0 // Arduino pin connected to VRX pin
#define VRY_PIN A1 // Arduino pin connected to VRY pin

#define yStepPin 2
#define yDirPin 5
#define statusLight 6
#define xStepPin 7
#define xDirPin 9
#define swPin 4
#define fineSwitch 3
// each step is 5 micrometers
#define STEP_DISTANCE 5
int j = 0;
bool singleStep = true;
bool step = false;

#define counterClockwise HIGH
#define clockwise LOW

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

int xPos = 0;
int yPos = 0;
bool xSign = true;
bool ySign = false;

void setup()
{
  Serial.begin(9600);

  pinMode(xStepPin, OUTPUT); // sets the digital pin 13 as output
  pinMode(xDirPin, OUTPUT);
  pinMode(yStepPin, OUTPUT); // sets the digital pin 13 as output
  pinMode(yDirPin, OUTPUT);
  pinMode(statusLight, OUTPUT);
  digitalWrite(statusLight, LOW);
  pinMode(swPin, INPUT_PULLUP);
}

void loop()
{
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  bool readState = digitalRead(swPin) != HIGH;
  // Serial.println(digitalRead(fineSwitch));
  //   Serial.println(readState);
  // Serial.println(digitalRead(swPin));
  if (readState)
  {
    while (digitalRead(swPin) != HIGH)
    {
      // Serial.println(digitalRead(swPin));
    }
    delay(600);
    singleStep = !singleStep;
  }

  // singleStep = digitalRead(fineSwitch) == HIGH;

  if (singleStep)
  {
    digitalWrite(statusLight, HIGH);
  }
  else
  {
    digitalWrite(statusLight, LOW);
  }

  // print data to Serial Monitor on Arduino IDE
  // Serial.print("x = ");
  // Serial.print(xValue);
  // Serial.print(", y = ");
  // Serial.println(yValue);
  // delay(200);

  int deltaX = xValue - 512;
  int deltaY = yValue - 512;

  float xPercent = deltaX / 512.0;
  float yPercent = deltaY / 512.0;

  // int motorSpeed = 200;
  // int xSteps = abs((int)(xPercent*motorSpeed));
  // int ySteps = abs((int)(yPercent*motorSpeed));

  if (!singleStep)
  {
    int motorSpeedDelay = 1200;
    float xSpeed = motorSpeedDelay + motorSpeedDelay * (1 - xPercent);
    float ySpeed = motorSpeedDelay + motorSpeedDelay * (1 - yPercent);

    if (deltaX >= 0)
    {
      xSign = false;
      digitalWrite(xDirPin, counterClockwise);
    }
    else
    {
      xSign = true;
      digitalWrite(xDirPin, clockwise);
    }
    if (deltaY >= 0)
    {
      ySign = false;
      digitalWrite(yDirPin, counterClockwise);
    }
    else
    {
      ySign = true;
      digitalWrite(yDirPin, clockwise);
    }

    if (deltaX < -60 || deltaX > 60)
    {
      if (xSign)
      {
        xPos += STEP_DISTANCE;
      }
      else
      {
        xPos -= STEP_DISTANCE;
      }
      digitalWrite(xStepPin, HIGH); // sets the digital pin 13 on
      delayMicroseconds(motorSpeedDelay);
      digitalWrite(xStepPin, LOW); // sets the digital pin 13 on
      delayMicroseconds(motorSpeedDelay);
      // Serial.println(xSpeed);
    }

    // Serial.println("X Stepped" + xSteps);
    if (deltaY < -60 || deltaY > 60)
    {

      if (ySign)
      {
        yPos += STEP_DISTANCE;
      }
      else
      {
        yPos -= STEP_DISTANCE;
      }
      digitalWrite(yStepPin, HIGH);       // sets the digital pin 13 off
      delayMicroseconds(motorSpeedDelay); // waits for a milisecond
      digitalWrite(yStepPin, LOW);        // sets the digital pin 13 off
      delayMicroseconds(motorSpeedDelay); // waits for a milisecond
                                          // Serial.println(ySpeed);
    }
  }
  else
  {
    if (deltaX >= 0)
    {
      xSign = false;
      digitalWrite(xDirPin, clockwise);
    }
    else
    {
      xSign = true;
      digitalWrite(xDirPin, counterClockwise);
    }
    if (deltaY >= 0)
    {
      ySign = false;
      digitalWrite(yDirPin, clockwise);
    }
    else
    {
      ySign = true;
      digitalWrite(yDirPin, counterClockwise);
    }

    if (deltaX < -256 || deltaX > 256)
    {
      if (xSign)
      {
        xPos += STEP_DISTANCE;
      }
      else
      {
        xPos -= STEP_DISTANCE;
      }
      step = true;
      // Serial.println("step x");
      digitalWrite(xStepPin, HIGH); // sets the digital pin 13 on
      delayMicroseconds(1000);
      digitalWrite(xStepPin, LOW); // sets the digital pin 13 on
      delayMicroseconds(1000);
    }

    // Serial.println("X Stepped" + xSteps);
    if ((deltaY < -256 || deltaY > 256))
    {
      if (ySign)
      {
        yPos += STEP_DISTANCE;
      }
      else
      {
        yPos -= STEP_DISTANCE;
      }
      step = true;
      // Serial.println("step y");
      digitalWrite(yStepPin, HIGH); // sets the digital pin 13 off
      delayMicroseconds(1000);      // waits for a milisecond
      digitalWrite(yStepPin, LOW);  // sets the digital pin 13 off
      delayMicroseconds(1000);      // waits for a milisecond
                                    // Serial.println(ySpeed);
    }
    // require joystick to be reset to position to 412 <= x, y <= 612
    while (step && ((xValue < 412 || xValue > 612) || (yValue < 412 || yValue > 612)))
    {
      xValue = analogRead(VRX_PIN);
      yValue = analogRead(VRY_PIN);
    }
  }
  step = false;
  Serial.print("(");
  Serial.print(xPos);
  Serial.print(", ");
  Serial.print(yPos);
  Serial.println(")");

  //  Serial.println("Y Stepped"+ ySteps);
}

/*
 *KIND OF BUGGY FIRST IMPLEMENTATION;
 *DOESNT STEP HOW YOU WANT.
 */

// #define VRX_PIN  A0 // Arduino pin connected to VRX pin
// #define VRY_PIN  A1 // Arduino pin connected to VRY pin

// #define xStepPin 2
// #define xDirPin 5
// #define statusLight 6
// #define yStepPin 7
// #define yDirPin 9
// int j = 0;

// #define counterClockwise HIGH
// #define clockwise LOW

// int xValue = 0; // To store value of the X axis
// int yValue = 0; // To store value of the Y axis

// void setup() {
//   Serial.begin(9600);

//   pinMode(xStepPin, OUTPUT); // sets the digital pin 13 as output
//   pinMode(xDirPin, OUTPUT);
//   pinMode(yStepPin, OUTPUT); // sets the digital pin 13 as output
//   pinMode(yDirPin, OUTPUT);
//   pinMode(statusLight, OUTPUT);
//   digitalWrite(statusLight,LOW);
// }

// void loop() {
//     // read analog X and Y analog values
//     xValue = analogRead(VRX_PIN);
//     yValue = analogRead(VRY_PIN);

//     // print data to Serial Monitor on Arduino IDE
//     Serial.print("x = ");
//     Serial.print(xValue);
//     Serial.print(", y = ");
//     Serial.println(yValue);
//     delay(200);

//     int deltaX = xValue -512;
//     int deltaY = yValue -512;

//     float xPercent = deltaX/512.0;
//     float yPercent = deltaY/512.0;

//     int motorSpeed = 200;
//     int xSteps = abs((int)(xPercent*motorSpeed));
//     int ySteps = abs((int)(yPercent*motorSpeed));

//     if(deltaX >=0){
//         digitalWrite(xDirPin,clockwise);
//     }else{
//         digitalWrite(xDirPin,counterClockwise);
//     }
//     if(deltaY >=0){
//         digitalWrite(yDirPin,clockwise);
//     }else{
//         digitalWrite(yDirPin,counterClockwise);
//     }

//     if(deltaX<20 || deltaX >20){
//         for(int x = 0; x<xSteps; x++){
//             digitalWrite(xStepPin, HIGH); // sets the digital pin 13 on
//             delayMicroseconds(1000);
//             digitalWrite(xStepPin, LOW); // sets the digital pin 13 on
//             delayMicroseconds(1000);
//         }
//     }

//     // Serial.println("X Stepped" + xSteps);
//     Serial.println(xSteps);
//     if(deltaY<20 || deltaY >20){
//         for(int y=0; y<ySteps; y++){
//             digitalWrite(yStepPin, HIGH); // sets the digital pin 13 off
//             delayMicroseconds(1000); // waits for a milisecond
//             digitalWrite(yStepPin, LOW); // sets the digital pin 13 off
//             delayMicroseconds(1000); // waits for a milisecond
//         }
//     }

//     //  Serial.println("Y Stepped"+ ySteps);
//      Serial.println(ySteps);

// }

/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */

// #define VRX_PIN  A0 // Arduino pin connected to VRX pin
// #define VRY_PIN  A1 // Arduino pin connected to VRY pin

// int xValue = 0; // To store value of the X axis
// int yValue = 0; // To store value of the Y axis

// void setup() {
//   Serial.begin(9600) ;
// }

// void loop() {
//   // read analog X and Y analog values
//   xValue = analogRead(VRX_PIN);
//   yValue = analogRead(VRY_PIN);

//   // print data to Serial Monitor on Arduino IDE
//   Serial.print("x = ");
//   Serial.print(xValue);
//   Serial.print(", y = ");
//   Serial.println(yValue);
//   delay(200);
// }

/*
 *BLINK
 */
// void setup()
// {
//     pinMode(13, OUTPUT); // sets the digital pin 13 as output
// }

// void loop()
// {
//     digitalWrite(13, HIGH); // sets the digital pin 13 on
//     delay(1000);            // waits for a second
//     digitalWrite(13, LOW);  // sets the digital pin 13 off
//     delay(1000);            // waits for a second
// }

/*
 *Main Program
 */
// #define xStepPin 2
// #define xDirPin 5
// #define status 6
// #define yStepPin 7
// #define yDirPin 9
// int j = 0;
// void setup()
// {
//   pinMode(xStepPin, OUTPUT); // sets the digital pin 13 as output
//   pinMode(xDirPin, OUTPUT);
//   pinMode(yStepPin, OUTPUT); // sets the digital pin 13 as output
//   pinMode(yDirPin, OUTPUT);
//   pinMode(status, OUTPUT);
// }

// void loop()
// {

//   if (j >= 0)
//   {
//     digitalWrite(status, HIGH);
//     for (int i = 0; i < 200; i++)
//     {
//       digitalWrite(xStepPin, HIGH); // sets the digital pin 13 on
//       digitalWrite(yStepPin, HIGH);
//       delayMicroseconds(1000);     // waits for a second
//       digitalWrite(xStepPin, LOW); // sets the digital pin 13 off
//       digitalWrite(yStepPin, LOW); // sets the digital pin 13 off

//       delayMicroseconds(1000); // waits for a second
//     }
//     j++;
//   }
//   if (j % 2 == 0)
//   {
//     digitalWrite(xDirPin, HIGH);
//     digitalWrite(yDirPin, HIGH);
//   }
//   else
//   {
//     digitalWrite(xDirPin, LOW);
//     digitalWrite(yDirPin, LOW);
//   }
//   delay(1000);
//   digitalWrite(status, LOW);
// }
