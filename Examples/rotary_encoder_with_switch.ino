#include "RotaryEncoderWithSwitch.h";

RotaryEncoderWithSwitch encoder;

void setup() {
  encoder.Init(5, 4, 12);
  Serial.begin(9600);
}

void loop() {
  static int8_t c, val;

  encoder.Update();

  if ( val = encoder.RotaryValue() ) {
    c += val;
    Serial.println(c);
  }

  if (encoder.ButtonLowered()) {
    Serial.println("button down");
  }
}
