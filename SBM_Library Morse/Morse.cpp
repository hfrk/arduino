/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Morse.h"

Morse::Morse(int pin, bool activeState)
{
  _pin = pin;
  _activeState = activeState;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, !activeState);
}

void Morse::dot()
{
  digitalWrite(_pin, _activeState);
  delay(250);
  digitalWrite(_pin, !_activeState);
  delay(250);  
}

void Morse::dash()
{
  digitalWrite(_pin, _activeState);
  delay(1000);
  digitalWrite(_pin, !_activeState);
  delay(250);
}
