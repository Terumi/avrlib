int latchPin = 8;
int dataPin = 11;
int clockPin = 10;

byte switchVar1 = 72; //01001000

void setup()
{
    Serial.begin(9600);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT);
}

void loop()
{

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

byte shiftIn(int myDataPin, int myClockPin)
{
    int i;
    byte myDataIn = 0;
    int temp;

    for (i = 7; i >= 0; i--)
    {
        digitalWrite(myClockPin, 0);
        delay(.02);

        temp = digitalRead(myDataPin);
        if (temp)
        {
            myDataIn = myDataIn | (1 << i);
        }
        digitalWrite(myClockPin, 1);
    }
    return myDataIn;
}