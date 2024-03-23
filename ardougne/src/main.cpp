#include <Arduino.h>

#define xStepPin 2
#define xDirPin 5
#define status 6
#define yStepPin 7
#define yDirPin 9
int j = 0;
void setup()
{
  pinMode(xStepPin, OUTPUT); // sets the digital pin 13 as output
  pinMode(xDirPin, OUTPUT);
  pinMode(yStepPin, OUTPUT); // sets the digital pin 13 as output
  pinMode(yDirPin, OUTPUT);
  pinMode(status, OUTPUT);
}

void loop()
{

  if (j >= 0)
  {
    digitalWrite(status, HIGH);
    for (int i = 0; i < 200; i++)
    {
      digitalWrite(xStepPin, HIGH); // sets the digital pin 13 on
      digitalWrite(yStepPin, HIGH);
      delayMicroseconds(1000);     // waits for a second
      digitalWrite(xStepPin, LOW); // sets the digital pin 13 off
      digitalWrite(yStepPin, LOW); // sets the digital pin 13 off

      delayMicroseconds(1000); // waits for a second
    }
    j++;
  }
  if (j % 2 == 0)
  {
    digitalWrite(xDirPin, HIGH);
    digitalWrite(yDirPin, HIGH);
  }
  else
  {
    digitalWrite(xDirPin, LOW);
    digitalWrite(yDirPin, LOW);
  }
  delay(1000);
  digitalWrite(status, LOW);
}
