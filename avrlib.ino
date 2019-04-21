#define CLK 4
#define DATA 5

void setup() {
  pinMode(CLK, INPUT);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DATA, INPUT);
  pinMode(DATA, INPUT_PULLUP);
  Serial.begin (115200);
  Serial.println("KY-040 Start:");
}

static uint8_t prevNextCode = 0;
static uint8_t store = 0;

void loop() {
  static int8_t c, val;

  if ( val = read_rotary() ) {
    c += val;
    Serial.print(c); Serial.print(" ");

    /*
        if ( prevNextCode == 0x0b) {
          Serial.println(store, BIN);
        }

        if ( prevNextCode == 0x07) {
          Serial.println(store, BIN);
        }

    */
  }
}

// A vald CW or  CCW move returns 1, invalid returns 0.
int8_t read_rotary() {
  static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
  prevNextCode <<= 2; //make space for the next data
  if (digitalRead(DATA)) prevNextCode |= 0x02; // make the second to last digit 1 (if not already 1). eg. xx1x
  if (digitalRead(CLK)) prevNextCode |= 0x01;  // make the last digit 1 (if not already). eg. xxx1
  prevNextCode &= 0x0f; // keep only the last 4 digits of prevNextCode

  /*
      If prevNextCode is a valid number, we want to check if that the current state came after the a valid state.
      Seven can only come from the state 01 (xx.01 -> 01.11) remember the first two digits of this number is the previous state.
      Accordingly, the Eleven state, can only come from the state 10 (xx.10 -> 10.11)
      For this reason we will be checking the 8 last digits of the store variable.
      Because its last 4 are the current prevNextCode and the first 4 are the previous prevNextCode.
      We could as well check for a 12 bit number but that requires to change the store var to uint16_t.
  */

  if  (rot_enc_table[prevNextCode] ) {
    store <<= 4; // make space for the next data
    store |= prevNextCode; // "append" prevNextCode to store. The appending happens only because store has now four 0 digits in the end.

    // if ((store & 0xfff) == 0x42b) return -1; // we need to find 0100 0010 1011
    // if ((store & 0xfff) == 0x817) return 1; // we need to find 1000 0001 0111

    if ((store & 0xff) == 0x2b) return -1; // we need to find 0010 1011
    if ((store & 0xff) == 0x17) return 1; // we need to find 0001 0111

  }
  return 0;
}
