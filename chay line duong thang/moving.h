#ifndef MOVING_H
#define MOVING_H

#include "Arduino.h"
#include "string.h"
#include "stdio.h"

class MOTOR
{
  public:
    void pidgiamxung(int xung);
    void pidtangxung(int xung);
    void setpin(uint8_t pwmpin, uint8_t pin);
    void Forward();
    void Backward();
    void tocdo(uint8_t tocdomax, uint8_t buocnhay);
    void tangtoc();
    void giamtoc();
    void Stop();
    void Stop1();
    int tocdo();
  private:  //  Declare private variables in class.
    uint8_t _pwmpin;  //  PWM-pin.
    uint8_t _pin;  //  Direction-pin.

    uint8_t _tocdo;
    uint8_t _tocdomax;
    uint8_t _buocnhay;

};

#endif
