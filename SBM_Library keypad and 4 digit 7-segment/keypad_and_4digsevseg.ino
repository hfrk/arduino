// Ananda Hafidh R K
// 19/439605/TK/48335

#include "KeypadLibrary.h"
#include "SegmentSeven.h"

#define ROWS 4
#define COLS 4

byte Cpins[COLS] = {7, 6, 5, 4};
byte Rpins[ROWS] = {11, 10, 9, 8};
char KEYS[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte Digs[4] = {0, 2, 12, 13};
byte Segment[7] = {A4, 3, A1, A2, A3, A5, A0};

Keypad_4x4 keypad(Cpins, Rpins, KEYS);
SegmentSeven_4digit seg7(Digs, Segment, LOW);

void setup() {
}

void loop() {
  char pressed_key = keypad.readKeypad();
  if (pressed_key){
    if (pressed_key == '*') seg7.pop();
    else if(pressed_key == '#') seg7.clear();
    else seg7.push(pressed_key);
  }
  seg7.display();
}
