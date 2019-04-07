/*
  ShiftRegister.h - Library for using a shift register.
  Created Tasos Protopapas, April 4, 2019.
  Released into the public domain.
*/

#ifndef ShiftRegister_h
#define ShiftRegister_h
#define NUMBER_OF_REGISTERS 2

#include "Arduino.h"

class ShiftRegister
{
  public:
    ShiftRegister(int clockPin, int latchPin, int dataPin);
    shiftDataOut(byte *data);
  private:
    byte getPage();
    int _latchPin;
    int _clockPin;
    int _dataPin;
};

#endif
