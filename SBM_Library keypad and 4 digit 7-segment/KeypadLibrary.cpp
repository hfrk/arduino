// Ananda Hafidh R K
// 19/439605/TK/48335

#include "KeypadLibrary.h"

Keypad_4x4::Keypad_4x4(byte colPins[4], byte rowPins[4], char keys[4][4]) {
  for (int i = 0; i<4; i++) {
    _colPins[i] = colPins[i];
    _rowPins[i] = rowPins[i];
    _keys[i][0] = keys[i][0];
    _keys[i][1] = keys[i][1];
    _keys[i][2] = keys[i][2];
    _keys[i][3] = keys[i][3];
    pinMode(_colPins[i], INPUT_PULLUP);
    pinMode(_rowPins[i], OUTPUT);
  }
}

char Keypad_4x4::readKeypad() {
  for (int M = 0; M<4; M++) {
    digitalWrite(_rowPins[M], LOW);
    for (int N = 0; N<4; N++) {
      if (util_isPressed(_colPins[N]) && util_debouncing(_colPins[N])) {
        // (M,N) is pressed
        digitalWrite(_rowPins[M], HIGH);
        return _keys[M][N];
      }
    }
    digitalWrite(_rowPins[M], HIGH);
  }
  return 0; // no key pressed
}

bool Keypad_4x4::util_isPressed(byte btn) {
  return digitalRead(btn) == LOW; // active LOW
}

bool Keypad_4x4::util_debouncing(byte btn) {
  delay(10);
  if (util_isPressed(btn)) {
    delay(10);
    while (util_isPressed(btn)) {};
    return true;
  }
  return false;
}
