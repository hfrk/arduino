// Ananda Hafidh R K
// 19/439605/TK/48335

int pins[] = {13, 12, 11, 10, 9, 8, 7};
            //A, B, C, D, E, F, G
int NIU[] = {4, 3, 9, 6, 0, 5};

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
    digitalWrite(pins[i], digit[num][i]);
  }
}

void setup() {
  for (int i = 7; i<=13; i++) pinMode(i, OUTPUT);
}

void loop() {
  for (int i = 0; i<6; i++) {
    display(NIU[i]);
    delay(1000);
  }
  //clear
  for (int i = 0; i<7; i++) digitalWrite(pins[i], HIGH);
  delay(1000);
}