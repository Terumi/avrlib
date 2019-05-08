#include "ShiftRegister.h";

//ShiftRegister::ShiftRegister(int clockPin, int latchPin, int dataPin)
ShiftRegister regist(10, 8, 11, 2);

void setup()
{
  Serial.begin(9600);
}

byte previousState[2];
byte data[2];


void loop()
{

  regist.shiftDataOut(data);


  for (int i = 0; i < 2; i++)
  {
    if (data[i] != previousState[i])
    {
      Serial.print("data ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(data[i], BIN);
      previousState[i] = data[i];
        Serial.println("");
  Serial.println("");

    }
  }
}
