/*
  RotaryEncoder.h - Library for using a rotary encoder.
  Created Tasos Protopapas, April 20, 2019.
  Original code by John Main / best-microcontroller-projects.com
*/

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

class RotaryEncoder {
  public:
    RotaryEncoder() {};

    void Init(int PIN_A, int PIN_B) {
      pin_A_ = PIN_A;
      pin_B_ = PIN_B;
     
      pinMode(pin_A_, INPUT_PULLUP);
      pinMode(pin_B_, INPUT_PULLUP);
      
      prevNextCode_ = 0;
      store_ = 0;
    }

    int8_t Read() {
      static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
      prevNextCode_ <<= 2; //make space for the next data
      if (digitalRead(pin_A_)) prevNextCode_ |= 0x02; // make the second to last digit 1 (if not already 1). eg. xx1x
      if (digitalRead(pin_B_)) prevNextCode_ |= 0x01;  // make the last digit 1 (if not already). eg. xxx1
      prevNextCode_ &= 0x0f; // keep only the last 4 digits of prevNextCode

      /*
          If prevNextCode is a valid number, we want to check if that the current state came after the a valid state.
          Seven can only come from the state 01 (xx.01 -> 01.11) remember the first two digits of this number is the previous state.
          Accordingly, the Eleven state, can only come from the state 10 (xx.10 -> 10.11)
          For this reason we will be checking the 8 last digits of the store_ variable.
          Because its last 4 are the current prevNextCode and the first 4 are the previous prevNextCode.
          We could as well check for a 12 bit number but that requires to change the store_ var to uint16_t.
      */

      if  (rot_enc_table[prevNextCode_] ) {
        store_ <<= 4; // make space for the next data
        store_ |= prevNextCode_; // "append" prevNextCode to store_. The appending happens only because store_ has now four 0 digits in the end.

        // if ((store_ & 0xfff) == 0x42b) return -1; // we need to find 0100 0010 1011
        // if ((store_ & 0xfff) == 0x817) return 1; // we need to find 1000 0001 0111

        if ((store_ & 0xff) == 0x2b) return -1; // we need to find 0010 1011
        if ((store_ & 0xff) == 0x17) return 1; // we need to find 0001 0111

      }
      return 0;
    }

  private:
    int pin_A_;
    int pin_B_;
    int8_t prevNextCode_;
    int8_t store_;
};
#endif
