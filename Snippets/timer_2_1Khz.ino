void setup()
{
    noInterrupts();
    Serial.begin(9600);
    TCNT2 = 0;  // reset timer/counter2
    TCCR2A = 0; // reset its control register

    OCR2A = 249;             // set output compare register TOP value. It should reach 250 as maximum.
    TCCR2A |= (1 << CS22);   //prescaler of 64
    TCCR2A |= (1 << WGM21);  // CTC mode (clear on compare)
    TIMSK2 |= (1 << OCIE2A); // enable timer compare interrupt
    interrupts();
}

ISR(TIMER2_COMPA_vect){}