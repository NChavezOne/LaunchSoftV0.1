/*
  StartupSound.h - A library perfect for sounds to play on a buzzer
  as soon as your favorite mircrocontroller boots up.
  May 28, 2019
 */

#include "Arduino.h"
#include "StartupSound.h"

StartupSound::StartupSound(int pin, int pin2, int pin3)
{
  pinMode(pin, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  _pin = pin;
  _pin2 = pin2;
  _pin3 = pin3;
}

void StartupSound::tune1()
{
  tone(_pin, 523.25, 400);
  tone(_pin3, 523.25, 400);
  delay(500);
  
  tone(_pin, 523.25, 100);
  tone(_pin3, 523.25, 100);
  delay(100);
  tone(_pin, 587.33, 100);
  tone(_pin3, 587.33, 100);
  delay(100);
  tone(_pin, 659.26, 100);
  tone(_pin3, 659.26, 100);
  delay(100);
  tone(_pin, 698.46, 100);
  tone(_pin3, 698.46, 100);
  delay(100);
}

void StartupSound::tune2()
{
  tone(_pin, 500, 200);
  delay(250);
  tone(_pin, 500, 200);
  delay(250);
  tone(_pin, 500, 200);
  delay(250);
}

void StartupSound::tune3()
{
  tone(_pin, 1046, 50);
  delay(100);
  tone(_pin, 1318, 50);
  delay(100);
  tone(_pin, 1567, 50);
  delay(100);
  tone(_pin, 1046, 50);
  delay(100);
  tone(_pin, 1318, 50);
  delay(100);
  tone(_pin, 1567, 50);
  delay(100);
}

void StartupSound::tune4()
{
  digitalWrite(_pin2, HIGH);
  tone(_pin,1046);
  delay(40);
  digitalWrite(_pin2, LOW);
  tone(_pin,2093);
  delay(40);
  noTone(_pin);
  delay(50);
  digitalWrite(_pin2, HIGH);
  tone(_pin,1318);
  delay(40);
  digitalWrite(_pin2, LOW);
  tone(_pin,2637);
  delay(40);
  noTone(_pin);
  delay(50);
  digitalWrite(_pin2, HIGH);
  tone(_pin,1568);
  delay(40);
  digitalWrite(_pin2, LOW);
  tone(_pin,3135);
  delay(40); 
  noTone(_pin);
  delay(50);
  digitalWrite(_pin2, HIGH);
  tone(_pin,2093);
  delay(40);
  digitalWrite(_pin2, LOW);
  tone(_pin,4186);
  delay(40);
  noTone(_pin);
  delay(50);
  noTone(_pin);
}

void StartupSound::mainBuzz()
{
  tone(_pin,4186);
  tone(_pin3,4186);
  digitalWrite(_pin2, HIGH);
  delay(400);
  noTone(_pin);
  noTone(_pin3);
  digitalWrite(_pin2, LOW);
  delay(500);
}
