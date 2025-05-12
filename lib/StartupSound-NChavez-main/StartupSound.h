/*
  StartupSound.h - A library perfect for sounds to play on a buzzer
  as soon as your favorite mircrocontroller boots up.
  May 28, 2019
 */
#ifndef StartupSound_h
#define StartupSound_h

#include "Arduino.h"

class StartupSound
{
  public:
    StartupSound(int pin, int pin2, int pin3);
    void tune1();
    void tune2();
    void tune3();
    void tune4();
    void mainBuzz();
  private:
    int _pin;  
    int _pin2;
    int _pin3;
};

#endif
