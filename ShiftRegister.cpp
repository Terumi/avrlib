/*
  ShiftRegister.cpp - Library for using a shift register.
  Created Tasos Protopapas, April 4, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(int clockPin, int latchPin, int dataPin, int number_of_registers)
{
  _latchPin = latchPin;
  _clockPin = clockPin;
  _dataPin = dataPin;
  _number_of_registers = number_of_registers;

  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, INPUT);
}

ShiftRegister::shiftDataOut(byte *data)
{

  // set latchPin LOW so the register loads data from its inputs
  digitalWrite(_latchPin, 0);
  // wait a little
  //delay(2000);
  //set it to HIGH to collect parallel data
  digitalWrite(_latchPin, 1);

  //for (int i = 0; i < sizeof(data); i++)
  for (int i = 0; i < _number_of_registers ; i++)
  {
    data[i] = ShiftRegister::getPage();
  }
}

byte ShiftRegister::getPage() {

  byte pageData = 0;


  for (int i = 7; i >= 0; i--)
  {
    // set clock pin to LOW in order to shift a bit
    digitalWrite(_clockPin, 0);

    //delay(50);
    //Serial.print(digitalRead(_dataPin));
   
    if (digitalRead(_dataPin)) {
      pageData = pageData | (1 << i);
    }
    // the job is done, so set it to HIGH
    digitalWrite(_clockPin, 1);
     
  }
  return pageData;
}
