// Ananda Hafidh R K
// 19/439605/TK/48335

int seg7[] = {13, 12, 11, 10, 9, 8, 7};
            //A, B, C, D, E, F, G
int inc_btn = 3;
int dec_btn = 2;
int count;

int digit[10][7] = { {LOW,LOW,LOW,LOW,LOW,LOW,HIGH},
                     {HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH},
                     {LOW,LOW,HIGH,LOW,LOW,HIGH,LOW},
                     {LOW,LOW,LOW,LOW,HIGH,HIGH,LOW},
                     {HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW},
                     {LOW,HIGH,LOW,LOW,HIGH,LOW,LOW},
                     {LOW,HIGH,LOW,LOW,LOW,LOW,LOW},
                     {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH},
                     {LOW,LOW,LOW,LOW,LOW,LOW,LOW},
                     {LOW,LOW,LOW,LOW,HIGH,LOW,LOW}
                   };

void display(int num) {
  for (int i = 0; i<7; i++){
    digitalWrite(seg7[i], digit[num][i]);
  }
}

void setup() {
  for (int i = 0; i <= 7; i++) pinMode(seg7[i], OUTPUT);
  pinMode(inc_btn, INPUT_PULLUP);
  pinMode(dec_btn, INPUT_PULLUP);
  count = 0;
}

#define isPressed(btn) (digitalRead(btn) == LOW)

bool debouncing(int btn) {
  delay(10);
  if (isPressed(btn)) {
    delay(10);
    while (isPressed(btn)) delay(1);
    return true;
  }
  return false;
}

void loop() {
  if (isPressed(inc_btn) && debouncing(inc_btn)) count++;
  if (isPressed(dec_btn) && debouncing(dec_btn)) count--;

  (count < 0) ? count += 10 : count %= 10;
  display(count);
  delay(10);
}
