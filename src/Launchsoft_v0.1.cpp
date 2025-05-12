#include <Arduino.h>
#include <SoftwareSerial.h>
/*
  Software for a simple rocket launch computer
  Nicholas Chavez 2025
*/

// These are the Arduino pins required to create a software seiral
//  instance. We'll actually only use the TX pin.
const int softwareTx = 8;
const int softwareRx = 7;

SoftwareSerial s7s(softwareRx, softwareTx);

//local pin defines

#define BUTTON_PIN 2
#define BUZZER_PIN 3
#define RELAY_PIN 4

// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void clearDisplay()
{
  s7s.write(0x76);  // Clear display command
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void setBrightness(byte value)
{
  s7s.write(0x7A);  // Set brightness command byte
  s7s.write(value);  // brightness data byte
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}

void neutralDisplay() 
{
  //send cursor to furthest left position
  for (int i = 0; i <= 3; i++) {
    s7s.write(0x79); //cursor control
    s7s.write(i); //move to i

    s7s.write(0b00101101); //central segment
  }
}

void setup() {
  s7s.begin(9600);
  Serial.begin(9600);

  // Clear the display, and then turn on all segments and decimals
  clearDisplay();  // Clears display, resets cursor
  setBrightness(255);  // High brightness

  neutralDisplay();

  //pinmodes
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

int i = 30;

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON_PIN) == LOW) {
    while (i >= 0) {
      clearDisplay();
      s7s.print(i);
      tone(BUZZER_PIN, 2000, 200);
      delay(800);
      if (i == 0) {
        digitalWrite(RELAY_PIN, HIGH);
        tone(BUZZER_PIN, 2000);
        while(1) {}
      }
      i--;
    }
  }
}