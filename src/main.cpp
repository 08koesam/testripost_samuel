#include <Arduino.h>
#include "Bounce2.h"

#define TransistorPNPlinks   8
#define TransistorNPNlinks   7
#define TransistorNPNrechts  A3
#define TransistorPNPrechts  A4

#define T1 4
#define T2 5
#define LED1 2
#define LED2 3

Bounce2::Button Taster1 = Bounce2::Button();
Bounce2::Button Taster2 = Bounce2::Button();

uint8_t zustand = 0; // 0 = links, 1 = rechts

// -------------------------------------------------

void motorAus()
{
  digitalWrite(TransistorNPNlinks, LOW);
  digitalWrite(TransistorNPNrechts, LOW);
  digitalWrite(TransistorPNPlinks, HIGH);   // PNP AUS
  digitalWrite(TransistorPNPrechts, HIGH);  // PNP AUS
}

void motorLinks()
{
  motorAus();
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  zustand = 3;
  

  digitalWrite(TransistorPNPlinks, LOW);   // PNP EIN
  digitalWrite(TransistorNPNlinks, HIGH); // NPN EIN
}

void motorRechts()
{
  motorAus();
  zustand = 3;
  

    digitalWrite(TransistorPNPrechts, LOW);  // PNP EIN
    digitalWrite(TransistorNPNrechts, HIGH);  // NPN EIN
  }

// -------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pinMode(TransistorNPNlinks, OUTPUT);
  pinMode(TransistorNPNrechts, OUTPUT);
  pinMode(TransistorPNPlinks, OUTPUT);
  pinMode(TransistorPNPrechts, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Taster1.attach(T1, INPUT_PULLUP);
  Taster2.attach(T2, INPUT_PULLUP);
  Taster1.interval(5);
  Taster2.interval(5);

  motorAus();
  Serial.println("..Start..");
}

// -------------------------------------------------

void loop()
{
  Taster1.update();
  Taster2.update();

  if (Taster1.pressed())
  {
    zustand = 0;
    Serial.println("Richtung LINKS");
  }

  if (Taster2.pressed())
  {
    zustand = 1;
    Serial.println("Richtung RECHTS");
  }

  if (zustand == 0)
  {
    
    motorLinks();
  }
  else if (zustand == 1)
  {

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    motorRechts();
  }
}
