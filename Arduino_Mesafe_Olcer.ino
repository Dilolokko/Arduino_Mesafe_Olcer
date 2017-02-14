//Mahmut YETİŞİR
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
                                      //Pinleri global değişkenlere atıyoruz
int trig=32;
int echo=21;
int led=33;
int konum_son=50;
long mesafe,sure;

void setup() {                              // pinlerin input output ayarlarını yapıyoruz
  pinMode(A8,INPUT);
  pinMode(trig,OUTPUT);                     //sinyal yolladıgı pin
  pinMode(echo,INPUT);                      //sinyali aldığı pin
  pinMode(led, OUTPUT);
  lcd.begin(16,2);                          //lcd mizin 16x2 lik oldugunu gösteriyoruz
  Serial.begin(57600);                      //serial ekranda 57600 baudrate de gözükeceğini gösteriyoruz
}

void loop() {
    int konum=analogRead(A8);                //potansiyometrenin değerini alıyoruz
    digitalWrite(trig,HIGH);                  //trig pininden sinyali gönderiyoruz
    delay(1);                                 //sinyali gönderdikten sonra bekleme yapıyoruz
    digitalWrite(trig,LOW);                   //sinyal göndermeyi kesiyoruz
    sure=pulseIn(echo,HIGH);                   //sinyalin ne kadar süre de döndüğünü alıyoruz 
    mesafe=(sure/2)/29.1;                     //mesafeyi hesaplıyoruz
    if (mesafe>60 )                           //mesafe 60 dan kodları çalıştır
    {
      lcd.home();
      lcd.clear();
      lcd.print("Mesafe: NA");                    //NA yazdır
      konum_son=konum/20.45;                      //potansiyometreyi 1024 den 50 değerine çekiyoruz
      if(konum_son<5)                             //eğer potansiyometre 5 den küçükse değeri 5 yap
      {
        konum_son=5;
      }
      if(konum_son >= mesafe)                     //eğer mesafe potansiyometre limit değerden küçükse led i yak
      {
        digitalWrite(led,HIGH);
      }
      else
      {
        digitalWrite(led,LOW);                    //değilse led i kapat
      }
      Serial.print("Mesafe : ");
      Serial.print(mesafe);                       //serial ekrana yaz - baudrate 57600 de yazılacak kısım
      Serial.print(" - Konum : ");
      Serial.println(konum_son);
      delay(250);                                 //bekleme yap
    }

    else{                                         //eğer mesafe 60dan küçükse
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);                           //lcd ekranın 0x0 dan başlayarak yaz
      lcd.print("Mesafe: ");                        //lcd ekranda yazılacak kısım
      lcd.print(mesafe);
      lcd.print(" cm");
      lcd.setCursor(0,1);                           //lcd ekranda 0x1 den başlayarak yaz
      lcd.print("Konum: ");
      konum_son=konum/20.45;
      if(konum_son<5)                               //limit değeri en küçük 5 yap
      {
        konum_son=5;
      }
      if(konum_son >= mesafe)                       //limit değer mesafeden büyükse led i yak
      {
        digitalWrite(led,HIGH);
      }
      else                                          //değilse led i kapat
      {
        digitalWrite(led,LOW);
      }
      lcd.print(konum_son);
      lcd.print(" cm");                                     //lcd ekrana yazdır
      Serial.print("Mesafe : ");
      Serial.print(mesafe);           
      Serial.print(" - Konum : ");                          //seri ekrana yaz  
      Serial.println(konum_son);
      delay(250);                                           //bekleme yap
    }
   
}


