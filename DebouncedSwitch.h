#ifndef DEBOUNCED_SWITCH_H
#define DEBOUNCED_SWITCH_H

class DebouncedSwitch {
  public:
    DebouncedSwitch() {};

    void Init(int pin) {
      _pin = pin;
      pinMode(_pin, INPUT);
      state_ = 0xff;
    }

    byte Read() {
      state_ = (state_ << 1) | digitalRead(_pin);
      return state_;
    }

    byte lowered() {
      return state_ == 0x80;
    }
    byte raised() {
      return state_ == 0x7f;
    }
    byte high() {
      return state_ == 0xff;
    }
    byte low() {
      return state_ == 0x00;
    }
    byte state() {
      return state_;
    }

  private:
    byte state_;
    int _pin;

};

#endif
