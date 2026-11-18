// Segment pinleri: a b c d e f g
const byte SEG[7] = {2, 3, 4, 5, 6, 7, 8};
// Hane pinleri: solda (yüzler), orta (onlar), sağda (birler)
const byte DIG[3] = {9, 10, 11};

// Ortak anot kart + PNP hane transistörü varsayımı: LOW ile aç
const bool SEG_ON = LOW;
const bool DIG_ON = LOW;

// Bit sırası: bit0=a ... bit6=g
const byte FONT[10] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66,
  0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

unsigned long lastTick = 0;
int counter = 999;   // 999'dan başla
byte curDigit = 0;

void allDigitsOff() {
  for (byte i = 0; i < 3; i++) digitalWrite(DIG[i], !DIG_ON);
}

void setSegments(byte pattern) {
  for (byte i = 0; i < 7; i++) {
    bool on = (pattern >> i) & 1;
    digitalWrite(SEG[i], on ? SEG_ON : !SEG_ON);
  }
}

void setup() {
  for (byte i = 0; i < 7; i++) {
    pinMode(SEG[i], OUTPUT);
    digitalWrite(SEG[i], !SEG_ON);
  }
  for (byte i = 0; i < 3; i++) {
    pinMode(DIG[i], OUTPUT);
    digitalWrite(DIG[i], !DIG_ON);
  }
}

void loop() {
  // Sayıyı her saniye azalt (999 -> 0, sonra 999'a döner)
  if (millis() - lastTick >= 100) {
    lastTick = millis();
    counter = (counter + 999) % 1000;   // bir azalt, 0 iken 999 olur
  }

  byte d[3] = { counter / 100, (counter / 10) % 10, counter % 10 };

  // Baştaki sıfırları gizle: 7 yerine "  7", 42 yerine " 42"
  bool blank = (curDigit == 0 && counter < 100) ||
               (curDigit == 1 && counter < 10);
  byte pat = blank ? 0x00 : FONT[d[curDigit]];

  allDigitsOff();
  setSegments(pat);
  digitalWrite(DIG[curDigit], DIG_ON);
  delay(3);

  curDigit = (curDigit + 1) % 3;
}