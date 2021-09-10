// Ananda Hafidh R K
// 19/439605/TK/48335

#include "Morse.h"

Morse morseL(13, HIGH);
Morse morseTX(1, LOW);
Morse morseRX(0, LOW);

void setup()
{
}

void loop()
{
  morseL.dot(); morseL.dot(); morseL.dot();
  morseL.dash(); morseL.dash(); morseL.dash();
  morseL.dot(); morseL.dot(); morseL.dot();
  delay(3000);
  morseTX.dot(); morseTX.dot(); morseTX.dot();
  morseTX.dash(); morseTX.dash(); morseTX.dash();
  morseTX.dot(); morseTX.dot(); morseTX.dot();
  delay(3000);
  morseRX.dot(); morseRX.dot(); morseRX.dot();
  morseRX.dash(); morseRX.dash(); morseRX.dash();
  morseRX.dot(); morseRX.dot(); morseRX.dot();
  delay(3000);
}
