// Motorlar için kullanılan pinlerin tanımlanması
const int motorA1 = 5;  // L298N'in IN3 Girişi
const int motorA2 = 6;  // L298N'in IN1 Girişi
const int motorB1 = 10; // L298N'in IN2 Girişi
const int motorB2 = 9;  // L298N'in IN4 Girişi

// Döngüler için atanan rastgele değişkenler
int i = 0;
int j = 0;
// Bluetooth cihazından gelecek sinyalin değişkeni
int state;
// Standart Hız, 0-255 arası bir değer alabilir
int vSpeed = 255;

void setup()
{
    // Motor kontrol pinlerinin çıkış olarak ayarlanması
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    // 9600 baud hızında bir seri port açalım
    Serial.begin(9600);
}

void loop()
{
    // Bluetooth bağlantısını kontrol et ve arabanın durması gerektiğini belirle
    // Not: Bu özelliği aktif etmek için "//" işaretlerini kaldırın
    // if(digitalRead(BTState)==LOW) { state='S'; }

    // Seri porttan veri geldiğinde, bu veriyi 'state' değişkenine kaydet
    if (Serial.available() > 0)
    {
        state = Serial.read();
    }

    // Uygulamadan gelen hız seviyesini ayarla (Değerler 0-255 arasında olmalı)
    if (state == '0')
    {
        vSpeed = 0;
    }
    else if (state == '1')
    {
        vSpeed = 100;
    }
    else if (state == '2')
    {
        vSpeed = 180;
    }
    else if (state == '3')
    {
        vSpeed = 200;
    }
    else if (state == '4')
    {
        vSpeed = 255;
    }

    // Gelen veriye göre motorların hızını ve yönünü ayarla
    // Not: 'analogWrite' fonksiyonu, belirtilen pindeki voltajı ayarlar (PWM sinyali oluşturur)
    // F: İleri
    // G: İleri Sol
    // I: İleri Sağ
    // B: Geri
    // H: Geri Sol
    // J: Geri Sağ
    // L: Sola dön
    // R: Sağa dön
    // S: Durdur
    if (state == 'F')
    {
        analogWrite(motorA1, vSpeed);
        analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);
        analogWrite(motorB2, 0);
    }
    else if (state == 'G')
    {
        analogWrite(motorA1, vSpeed);
        analogWrite(motorA2, 0);
        analogWrite(motorB1, 100);
        analogWrite(motorB2, 0);
    }
    else
        // I: İleri Sağ
        else if (state == 'I')
        {
            analogWrite(motorA1, 100);
            analogWrite(motorA2, 0);
            analogWrite(motorB1, vSpeed);
            analogWrite(motorB2, 0);
        }
    // B: Geri
    else if (state == 'B')
    {
        analogWrite(motorA1, 0);
        analogWrite(motorA2, vSpeed);
        analogWrite(motorB1, 0);
        analogWrite(motorB2, vSpeed);
    }
    // H: Geri Sol
    else if (state == 'H')
    {
        analogWrite(motorA1, 0);
        analogWrite(motorA2, 100);
        analogWrite(motorB1, 0);
        analogWrite(motorB2, vSpeed);
    }
    // J: Geri Sağ
    else if (state == 'J')
    {
        analogWrite(motorA1, 0);
        analogWrite(motorA2, vSpeed);
        analogWrite(motorB1, 0);
        analogWrite(motorB2, 100);
    }
    // L: Sola dön
    else if (state == 'L')
    {
        analogWrite(motorA1, vSpeed);
        analogWrite(motorA2, 150);
        analogWrite(motorB1, 0);
        analogWrite(motorB2, 0);
    }
    // R: Sağa dön
    else if (state == 'R')
    {
        analogWrite(motorA1, 0);
        analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);
        analogWrite(motorB2, 150);
    }
    // S: Durdur
    else if (state == 'S')
    {
        analogWrite(motorA1, 0);
        analogWrite(motorA2, 0);
        analogWrite(motorB1, 0);
        analogWrite(motorB2, 0);
    }
}
