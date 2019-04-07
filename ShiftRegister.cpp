/*
  ShiftRegister.cpp - Library for using a shift register.
  Created Tasos Protopapas, April 4, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(int clockPin, int latchPin, int dataPin)
{
  _latchPin = latchPin;
  _clockPin = clockPin;
  _dataPin = dataPin;
 
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, INPUT);
}

ShiftRegister::shiftDataOut(byte *data)
{

  // set latchPin LOW so the register loads data from its inputs
  digitalWrite(_latchPin, 0);
  // wait a little
  //delayMicroseconds(.2);
  //set it to HIGH to collect parallel data
  digitalWrite(_latchPin, 1);

  for (int i = 0; i < sizeof(data); i++)
  {
    data[i] = ShiftRegister::getPage();
  }
}

byte ShiftRegister::getPage() {

  byte pageData = 0;

  for (int i = 7; i >= 0; i--)
  {
    // set clock pin to HIGH in order to shift a bit
    digitalWrite(_clockPin, 0);
    //delay(.02);

    if (digitalRead(_dataPin)) {
      pageData = pageData | (1 << i);
    }

    // the job is done, so set it to LOW
    digitalWrite(_clockPin, 1);
  }
  return pageData;
}
