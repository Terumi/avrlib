//#include "ShiftRegister.h";
#include <DebouncedSwitch.h>

int latchPin = 8;
int clockPin = 10;
int dataPin = 11;

int buttonPin = 2;

//byte previousState[2];
//ShiftRegister shiftRegister(clockPin, latchPin, dataPin);

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


int step = 0;

ISR(TIMER2_COMPA_vect) {

  /*
    byte data[2];
    shiftRegister.shiftDataOut(data);
    for (int i = 0; i < 2; i++) {
      if ( previousState[i] != data[i])
      {
        Serial.println(data[i], BIN);
        previousState[i] = data[i];
        Serial.println("----");
      }
    }
  */

  button.Read();
  if (button.lowered()) {
  Serial.println("lowered");
  }

  if (button.raised()) {
  Serial.println("raised");
  }


  if (step == 1000) {
  Serial.println(millis());
    step = 0;
  }
  step++;
}



void loop()
{
  
  //Serial.println(digitalRead(buttonPin));

  /*
    byte data[2];
    shiftRegister.shiftDataOut(data);

    for (int i = 0; i < 2; i++) {
      if ( previousState[i] != data[i])
      {
        Serial.println(data[i], BIN);
        previousState[i] = data[i];
        Serial.println("----");
      }
    }

    delay(10);
  */
  // delay(10);
}



/*


  int latchPin = 8;
  int dataPin = 11;
  int clockPin = 10;

  byte switchVar1 = 72;  //01001000

  void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
  }

  void loop() {

  //Pulse the latch pin:
  //set it to 0 to collect parallel data
  digitalWrite(latchPin, 0);
  // wait
  delayMicroseconds(.2);
  //set it to 1 to transmit data serially
  digitalWrite(latchPin, 1);

  switchVar1 = shiftIn(dataPin, clockPin);

  Serial.println(switchVar1, BIN);
  }

  byte shiftIn(int myDataPin, int myClockPin) {
  int i;
  byte myDataIn = 0;
  int temp;

  for (i = 7; i >= 0; i--)
  {
    digitalWrite(myClockPin, 0);
    delay(.02);

    temp = digitalRead(myDataPin);
    if (temp) {
      myDataIn = myDataIn | (1 << i);
    }
    digitalWrite(myClockPin, 1);
  }
  return myDataIn;
  }

*/
