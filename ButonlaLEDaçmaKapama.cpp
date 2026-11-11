/*


3. Devre Şeması ve Bağlantı Adımları

Güvenlik için bu işlemleri yaparken Arduino'nun USB kablosunu bilgisayardan çıkarın.
1. LED'i Yerleştirin: LED'i breadboard üzerinde iki farklı dikey sıraya gelecek şekilde takın. (Örn: Uzun bacak A5 deliğinde, kısa bacak A6 deliğinde olsun).
2. Direnci Bağlayın: Direncinizin bir bacağını, LED'in kısa bacağının (-) bulunduğu sıraya takın. Direncin diğer bacağını ise breadboard üzerinde boş bir sıraya takın. (Dirençlerin yönü fark etmez).
3. GND (Toprak) Bağlantısı: Bir jumper kablo alın. Bir ucunu Arduino üzerindeki GND pinine, diğer ucunu ise direncin boşta kalan bacağının sırasına takın. (Böylece LED'in eksisini korumalı olarak toprağa bağlamış olduk).
4. Sinyal (Pin) Bağlantısı: İkinci jumper kabloyu alın. Bir ucunu Arduino'nun 8 numaralı dijital pinine, diğer ucunu ise LED'in uzun bacağının (+) bulunduğu sıraya takın.

1. Butonu Yerleştirin: Butonu breadboard'un ortasındaki uzun kanalı (yarığı) ortalayacak şekilde bastırarak takın. (Bacakların ikisi kanalın üstünde, ikisi altında kalsın).
2. Toprak (GND) Bağlantısı: Bir jumper kablo ile butonun bir bacağını Arduino'nun boşta kalan bir GND pinine bağlayın.
3. Sinyal Bağlantısı: Diğer jumper kablo ile butonun (GND bağladığınız bacağın tam karşısındaki veya yanındaki) diğer bacağını Arduino'nun 7 numaralı dijital pinine bağlayın.

*/

const int ledPini = 8;    // LED'in bağlı olduğu pin
const int butonPini = 7;  // Butonun bağlı olduğu pin

void setup() {
  pinMode(ledPini, OUTPUT);
  
  // 7. pini giriş yapıyoruz ve dahili Pull-up direncini aktif ediyoruz
  pinMode(butonPini, INPUT_PULLUP);
}

void loop() {
  // Butonun durumunu okuyoruz (0 veya 1)
  int butonDurumu = digitalRead(butonPini);

  // Dahili pull-up kullandığımız için basıldığında sinyal LOW (0) olur
  if (butonDurumu == LOW) {
    digitalWrite(ledPini, HIGH); // Butona basılıyorsa LED'i yak
  } else {
    digitalWrite(ledPini, LOW);  // Buton bırakıldıysa LED'i söndür
  }
}
