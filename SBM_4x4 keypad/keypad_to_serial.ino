// Ananda Hafidh R K
// 19/439605/TK/48335

#define ROWS 4
#define COLS 4
#define isPressed(btn) (digitalRead(btn) == LOW) // active LOW

int Cpins[COLS] = {7, 6, 5, 4};
int Rpins[ROWS] = {11, 10, 9, 8};
char KEYS[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

bool debouncing(int btn) {
  delay(10);
  if (isPressed(btn)) {
    delay(10);
    while (isPressed(btn)) {};
    return true;
  }
  return false;
}

char ReadKeypad() {
  for (int M = 0;M<4;M++) {
    digitalWrite(Rpins[M], LOW);
    for (int N = 0;N<4;N++) {
      if (isPressed(Cpins[N]) && debouncing(Cpins[N])) {
        // (M,N) is pressed
        digitalWrite(Rpins[M], HIGH);
        return KEYS[M][N];
      }
    }
    digitalWrite(Rpins[M], HIGH);
  }
  return 0; // no key pressed
}

void setup() {
  Serial.begin(115200);
  for (int i = 0;i<4;i++) {
    pinMode(Cpins[i], INPUT_PULLUP);
    pinMode(Rpins[i], OUTPUT);
  }
}

void loop() {
  char pressed_key = ReadKeypad();
  if (pressed_key) Serial.print(pressed_key);
}
