#include "moving.h"
#include "Arduino.h"

void MOTOR:: setpin(uint8_t pwmpin, uint8_t pin)
{
  _pwmpin = pwmpin;
  _pin = pin;

  pinMode(_pwmpin, OUTPUT);
  pinMode(_pin, OUTPUT);
}
void MOTOR:: Forward()
{
  digitalWrite(_pin, 1);
}
void MOTOR:: Backward()
{
  digitalWrite(_pin, 0);
}
void MOTOR:: tocdo(uint8_t tocdomax, uint8_t buocnhay)
{
  _tocdomax = tocdomax;
  _buocnhay = buocnhay;
  _tocdo = 0;
}
void MOTOR:: tangtoc()
{
  if (_tocdo < _tocdomax)
  {
    _tocdo += _buocnhay;
  }
  else if (_tocdo > _tocdomax)
  {
    _tocdo = _tocdomax;
  }
  analogWrite(_pwmpin, _tocdo);
}
void MOTOR::pidtangxung(int xung)
{
  if (_tocdo < xung)
  {
    _tocdo += _buocnhay;
  }
  else if (_tocdo > xung)
  {
    _tocdo = xung;
  }
  analogWrite(_pwmpin, xung);
}
void MOTOR::pidgiamxung(int xung)
{
  if (_tocdo > xung)
  {
    _tocdo -= _buocnhay;
  }
  else if (_tocdo < xung)
  {
    _tocdo = xung;
  }
  analogWrite(_pwmpin, xung);
}
void MOTOR::Stop()
{
  if (_tocdo > 0)
  {
    _tocdo -= _buocnhay;
  }
  else if (_tocdo < 0)
  {
    _tocdo = 0;
  }
  else return;
  analogWrite(_pwmpin, _tocdo);
}
void MOTOR::Stop1()
{
  analogWrite(_pwmpin, 0);
}
int MOTOR::tocdo()
{
  return _tocdo;
}

