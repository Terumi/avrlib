#include "RotaryEncoder.h";

RotaryEncoder encoder;

void setup() {
  encoder.Init(5, 4);
  Serial.begin(9600);
}

void loop() {
  static int8_t c, val;

  if ( val = encoder.Read() ) {
    c += val;
    Serial.print(c); Serial.print(" ");
  }
}
