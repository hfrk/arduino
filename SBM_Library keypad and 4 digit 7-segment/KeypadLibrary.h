// Ananda Hafidh R K
// 19/439605/TK/48335

#ifndef KeypadLibrary_h
#define KeypadLibrary_h

#include "Arduino.h"

class Keypad_4x4
{
  public:
    Keypad_4x4(byte colPins[4], byte rowPins[4], char keys[4][4]);
    char readKeypad();
    
  private:
    bool util_isPressed(byte btn);
    bool util_debouncing(byte btn);
    uint8_t _rowPins[4];
    uint8_t _colPins[4];
    char _keys[4][4];
};

#endif
