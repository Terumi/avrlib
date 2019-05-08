/*
  ShiftRegister.h - Library for using a shift register.
  Created Tasos Protopapas, April 4, 2019.
  Released into the public domain.
*/

#ifndef ShiftRegister_h
#define ShiftRegister_h


#include "Arduino.h"

class ShiftRegister
{
  public:
    ShiftRegister(int clockPin, int latchPin, int dataPin, int number_of_registers);
    shiftDataOut(byte *data);
  private:
    byte getPage();
    int _latchPin;
    int _clockPin;
    int _dataPin;
    int _number_of_registers;
};

#endif
