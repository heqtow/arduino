/* Buzzerli mesafe sensörü
    
    Bağlantılar
    
    HC-SR04 Vcc → 5V
    HC-SR04 Trig → D9
    HC-SR04 Echo → D10
    HC-SR04 Gnd → GND
    Buzzer modülü VCC → 5V
    Buzzer modülü I/O → D8
    Buzzer modülü GND → GND

    Nasıl çalışır?
      
      100 cm’den uzakta buzzer sessiz.
      100 cm ile 10 cm arasında bip aralığı 800 ms’den 80 ms’ye düşer.
      10 cm ve daha yakında sürekli ses çalar.

*/

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

const float UZAK = 100.0;  // cm: bu mesafeden uzakta sessiz
const float YAKIN = 10.0;  // cm: bu mesafenin altında sürekli ses

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(buzzerPin, HIGH);  // başlangıçta sessiz (LOW tetikler)
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

float mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long sure = pulseIn(echoPin, HIGH, 30000);
  if (sure == 0) return -1;
  return sure * 0.0343 / 2.0;
}

void bip(int ms) {
  digitalWrite(buzzerPin, LOW);   // aç
  delay(ms);
  digitalWrite(buzzerPin, HIGH);  // kapat
}

void loop() {
  float d = mesafeOlc();
  Serial.println(d);

  if (d < 0 || d > UZAK) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    return;
  }

  if (d <= YAKIN) {
    digitalWrite(buzzerPin, LOW);   // sürekli ses
    delay(100);
    return;
  }

  // YAKIN ile UZAK arasında: mesafe azaldıkça bip aralığı kısalır
  int aralik = map((int)d, (int)YAKIN, (int)UZAK, 80, 800);
  bip(80);
  delay(aralik);
}
