// Ananda Hafidh R K
// 19/439605/TK/48335

int pins[] = {13, 12, 11, 10, 9, 8, 7};
            //A, B, C, D, E, F, G

int digit1[7] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH};
int digit2[7] = {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW};


void display1() {
  for (int i = 0; i<7; i++){
    digitalWrite(pins[i], digit1[i]);
  }
}

void display2() {
  for (int i = 0; i<7; i++){
    digitalWrite(pins[i], digit2[i]);
  }
}

void setup() {
  for (int i = 7;i<=13;i++) pinMode(i, OUTPUT);
}

void loop() {
  display1();
  delay(1000);
  display2();
  delay(1000);
}