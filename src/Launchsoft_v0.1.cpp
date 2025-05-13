
/*
  Software for a simple rocket launch computer
  Nicholas Chavez 2025
*/


//Public Libraries
#include <Arduino.h>
#include <SoftwareSerial.h>

//Personal Libraries
#include <StartupSound.h>

//local pin defines

#define BUTTON_PIN 2

#define BUZZER_PIN 3
#define BUZZER_PIN_2 4
#define BUZZER_PIN_3 5 //buzzer 3 is a passive buzzer that requires a logic low to sound

#define RELAY_PIN 4

// These are the Arduino pins required to create a software seiral
//  instance. We'll actually only use the TX pin.
const int softwareTx = 8;
const int softwareRx = 7;

SoftwareSerial s7s(softwareRx, softwareTx);

StartupSound buzzer(BUZZER_PIN, BUZZER_PIN_2 ,BUZZER_PIN_3);

//function defines

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

//personal functions
void neutralDisplay() 
{
  //send cursor to furthest left position
  for (int i = 0; i <= 3; i++) {
    s7s.write(0x79); //cursor control
    s7s.write(i); //move to i

    s7s.write(0b00101101); //central segment
  }
}
//go to the digit. 1 = furthest left digit
void goToDigit(int digit) {
  digit = digit - 1;
  s7s.write(0x79);
  s7s.write(digit);
}
void initDisplay() {
  for (int i = 1; i < 5; i++) {
    clearDisplay();
    goToDigit(i);
    s7s.write(0b00101101); //central segment
    delay(200);
  }
}
void soundBuzzer3() {
  tone(BUZZER_PIN_3, 1, 500);
}

//global variables

int countdown = 30;

//setup

void setup() {
  //pinmodes
  
  pinMode(BUZZER_PIN_3, OUTPUT);
  digitalWrite(BUZZER_PIN_3, LOW);
  
  s7s.begin(9600);
  Serial.begin(9600);

  // Clear the display, and then turn on all segments and decimals
  clearDisplay();  // Clears display, resets cursor
  setBrightness(255);  // High brightness

  neutralDisplay();
  buzzer.tune1();
  
  Serial.print("Device initializing.");
  for (int i =0; i < 5; i++) {
    Serial.print(".");
    delay(50);
  }
  Serial.println(".");
  
  bool allDevicesInitialized = true;
  if (allDevicesInitialized == true) {
    Serial.println("Device successfully initialized.");
  } else {
    buzzer.tune4();
    Serial.println("Device failed to initialized.");
  }

  delay(1000);
  buzzer.tune3();
  delay(800);
  initDisplay();
  buzzer.tune4();
  delay(1000);

  //pinmodes
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

//loop

long int timeElapsedSinceLastLoop = 0;
int previousMillis = 0;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = mills();
  if (currentMillis - previousMillis >= interval) {
    buzzer.tune4();
    idleCounter = 0;
  }
  idleCounter++;
  delay(1);
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Countdown buzzon pressed, launch sequence commencing.");
    delay(100);
    while (countdown >= 0) {
      timeElapsedSinceLastLoop = millis();
      clearDisplay();
      s7s.print(countdown);
      tone(BUZZER_PIN, 2000, 200);
      soundBuzzer3();
      if (countdown == 0) {
        digitalWrite(RELAY_PIN, HIGH);
        tone(BUZZER_PIN, 2000);
        while(1) {}
      }
      countdown--;
      while (millis() - timeElapsedSinceLastLoop <= 1000) {}
    } 
  }
}