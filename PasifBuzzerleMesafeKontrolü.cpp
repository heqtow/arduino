/*
  
  Bağlantılar
  
  HC-SR04 Vcc → 5V
  HC-SR04 Trig → D9
  HC-SR04 Echo → D10
  HC-SR04 Gnd → GND
  Buzzer  VCC → D8
  Buzzer GND → GND

*/

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

const float UZAK = 100.0;  // cm: bu mesafeden uzakta sessiz
const float YAKIN = 10.0;  // cm: bu mesafenin altında sürekli ses

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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

void loop() {
  float d = mesafeOlc();
  Serial.println(d);

  if (d < 0 || d > UZAK) {
    noTone(buzzerPin);
    delay(100);
    return;
  }

  if (d <= YAKIN) {
    tone(buzzerPin, 2000);   // sürekli ses
    delay(100);
    return;
  }

  // YAKIN ile UZAK arasında: mesafe azaldıkça bip aralığı kısalır
  int aralik = map((int)d, (int)YAKIN, (int)UZAK, 80, 800);
  tone(buzzerPin, 2000, 80);  // kısa bip, kendi kendine durur
  delay(aralik);
}
