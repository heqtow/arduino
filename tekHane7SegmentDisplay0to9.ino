// Sıra: a b c d e f g
// Arduino pinleri: D2 D3 D4 D5 D6 D7 D8
const byte SEG[7] = {2, 3, 4, 5, 6, 7, 8};

// Ortak katot için bit maskeleri (bit0=a ... bit6=g)
const byte DIGITS[10] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F  // 9
};

void showDigit(byte n) {
  byte pattern = DIGITS[n];
  for (byte i = 0; i < 7; i++) {
    // Ortak anot: segment yanması için LOW gerekir, bu yüzden tersle
    bool on = (pattern >> i) & 1;
    digitalWrite(SEG[i], on ? LOW : HIGH);
  }
}

void setup() {
  for (byte i = 0; i < 7; i++) {
    pinMode(SEG[i], OUTPUT);
  }
}

void loop() {
  for (byte n = 0; n <= 9; n++) {
    showDigit(n);
    delay(1000);
  }
}