/*
  RotaryEncoder.h - Library for using a rotary encoder.
  Created Tasos Protopapas, April 20, 2019.
  Original code by John Main / best-microcontroller-projects.com
*/



#ifndef RotaryEncoderWithSwitch_h
#define RotaryEncoderWithSwitch_h

#include "./DebouncedSwitch.h"
#include "./RotaryEncoder.h"

class RotaryEncoderWithSwitch {
  public:

    DebouncedSwitch Button_;
    RotaryEncoder Encoder_;

    RotaryEncoderWithSwitch() {};

    void Init(int PIN_A, int PIN_B, int PIN_BUTTON) {
      Encoder_.Init(PIN_A, PIN_B);
      Button_.Init(PIN_BUTTON);
    }

    uint8_t ButtonLowered() {
      return Button_.lowered();
    }

    byte ButtonState() {
      return Button_.state();
    }

    int8_t RotaryValue() {
      return Encoder_.Read();
    }

    void Update() {
      Button_.Read();
    }

  private:
    int pin_A_;
    int pin_B_;
    int pin_button_;
};
#endif
