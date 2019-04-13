#include "DebouncedSwitch.h"

int buttonPin = 2;

DebouncedSwitch button;

void setup()
{
  button.Init(2);
  Serial.begin(9600);
  noInterrupts();
  Serial.begin(9600);
  TCNT2 = 0; // reset timer/counter2
  TCCR2A = 0; // reset its control register

  OCR2A = 249; // set output compare register TOP value. It should reach 250 as maximum.
  TCCR2A |= (1 << CS22); //prescaler of 64
  TCCR2A |= (1 << WGM21);   // CTC mode
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
  interrupts();
}

ISR(TIMER2_COMPA_vect) {

  button.Read();

  if (button.lowered()) {
  Serial.println("lowered");
  }

  if (button.raised()) {
  Serial.println("raised");
  }
}



void loop()
{
  
}