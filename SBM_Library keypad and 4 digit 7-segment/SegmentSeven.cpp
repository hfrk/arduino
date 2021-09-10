// Ananda Hafidh R K
// 19/439605/TK/48335

#include "Arduino.h"
#include "SegmentSeven.h"

const int digit[15][7] = { 
                     {LOW,LOW,LOW,LOW,LOW,LOW,HIGH},      // 0
                     {HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH},  // 1
                     {LOW,LOW,HIGH,LOW,LOW,HIGH,LOW},     // 2
                     {LOW,LOW,LOW,LOW,HIGH,HIGH,LOW},     // 3
                     {HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW},    // 4
                     {LOW,HIGH,LOW,LOW,HIGH,LOW,LOW},     // 5
                     {LOW,HIGH,LOW,LOW,LOW,LOW,LOW},      // 6
                     {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH},   // 7
                     {LOW,LOW,LOW,LOW,LOW,LOW,LOW},       // 8
                     {LOW,LOW,LOW,LOW,HIGH,LOW,LOW},      // 9
                     {LOW,LOW,LOW,HIGH,LOW,LOW,LOW},      // a
                     {HIGH,HIGH,LOW,LOW,LOW,LOW,LOW},     // b
                     {LOW,HIGH,HIGH,LOW,LOW,LOW,HIGH},    // c
                     {HIGH,LOW,LOW,LOW,LOW,HIGH,LOW},     // d
                     {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH} // off
                   };

SegmentSeven_4digit::SegmentSeven_4digit(byte digitCOM[4], byte segmentPins[7], byte activeState) {
  isACTIVE_LOW = (activeState == LOW);

  clear(); // init buffer
  for (int i = 0; i < 7; i++) {
    _segmentPins[i] = segmentPins[i];
    pinMode(_segmentPins[i], OUTPUT);
    digitalWrite(_segmentPins[i], isACTIVE_LOW);
  }
  for (int i = 0; i < 4; i++) {
    _digitCOM[i] = digitCOM[i];
    pinMode(_digitCOM[i], OUTPUT);
    digitalWrite(_digitCOM[i], !isACTIVE_LOW);
  }
}

void SegmentSeven_4digit::display() {
  for(int i = 0; i<4; i++) {
    digitalWrite(_digitCOM[i], isACTIVE_LOW); // enable digit
    _sendDigit(_toBeDisplayed[i]);
    delay(5);
    _sendDigit(14); // clear digit
    digitalWrite(_digitCOM[i], !isACTIVE_LOW); // disable digit
  }
}

void SegmentSeven_4digit::push(char c) {
  for (int i = 0; i<3; i++) {
    _toBeDisplayed[i] = _toBeDisplayed[i+1];
  }
  _toBeDisplayed[3] = _toIndex(c);
  _buffer += c;
}

void SegmentSeven_4digit::clear() {
  _buffer = "    ";
  for (int i = 0; i<4; i++) _toBeDisplayed[i] = 14;
}

void SegmentSeven_4digit::pop() {
  int len = _buffer.length();
  if (len > 4) {
    for (int i = 3; i>0; i--) {
      _toBeDisplayed[i] = _toBeDisplayed[i-1];
    }
    _toBeDisplayed[0] = _toIndex(_buffer.charAt(len-5));
    _buffer.remove(len-1);
  }
}

void SegmentSeven_4digit::_sendDigit(int num) {
  if (isACTIVE_LOW) {
    for(int i = 0; i<7; i++)
      digitalWrite(_segmentPins[i], digit[num][i]);
  }
  else {
    for(int i = 0; i<7; i++)
      digitalWrite(_segmentPins[i], !digit[num][i]);
  }
}

int SegmentSeven_4digit::_toIndex(char c) {
  if (isDigit(c)) return c-'0'; // 0 to 9
  else if(c-'A'>=0 && c-'A'<4) return c-'A'+10; // to hex number (10 to 13)
  else return 14; // clear
}
