// Ananda Hafidh R K
// 19/439605/TK/48335

#ifndef SegmentSeven_h
#define SegmentSeven_h

#include "Arduino.h"

class SegmentSeven_4digit
{
  public:
  SegmentSeven_4digit(byte digitControl[4], byte segmentPins[7], byte activeState);
  void display();
  void push(char c);
  void clear();
  void pop();

  private:
  bool isACTIVE_LOW;
  String _buffer;
  int _toBeDisplayed[4];
  byte _digitCOM[4];
  byte _segmentPins[7];

  void _sendDigit(int num);
  int _toIndex(char c);
};

#endif
