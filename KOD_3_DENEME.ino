// EGAP_proje kodu==2 

#include <SoftwareSerial.h>
SoftwareSerial myBluetooth(10, 11); // RX, TX girişleri olarak 
int ledler[] = {2,3,8,12,13}; // KARA SİMSEK İÇİN LED BACAKLARI
//Sensör pinlerimizi tanımlıyoruz:
#define sensor_pin A0
#define buzzer_pin 9
//yangın sensör pini tanımlıyoruz.
#define alev_sensor 4
//RGB LED'imizin çıkış pinlerini tanımlıyoruz:
#define led_r 5
#define led_g 6
#define led_b 7
//Sensörün çalışması için gerekli ön ısıtma süresini 5sn olarak belirliyoruz
#define preheat_time 5000
//Alarmın çalması için gerekli eşik değerini 400 olarak belirliyoruz.
#define esikdeger 400

void setup()
{
  for(int i=0; i<6; i++){
    
  pinMode(ledler[i], OUTPUT);
  
  }
//Alarm için kullanacağımız buzzer ve LED'leri çıkış olarak tanımlıyoruz
pinMode(alev_sensor,INPUT); // ALEV SENSORU GİRİŞ OLARAK  AYARLIYOZ.
pinMode(buzzer_pin, OUTPUT);
pinMode(led_r, OUTPUT);
pinMode(led_g, OUTPUT);
pinMode(led_b, OUTPUT);
//Varsayılan olarak LED'in sönük kalmasını sağlıyoruz
digitalWrite(led_r,LOW);
digitalWrite(led_g,LOW);
digitalWrite(led_b,LOW);
//Sensör değerini seri monitörden görebilmemiz için seri haberleşmeyi başlatıyoruz:
Serial.begin(9600);
myBluetooth.begin(9600);// bluetooth serial monitörü
myBluetooth.println("GAZ KACAGI ERKEN UYARI SİSTEMİ");
//İlk 5sn boyunca sensörün ısınmasını bekliyoruz. Bu esnada LED mavi renkte yanıyor:
Serial.println("Sensor isitiliyor...");
digitalWrite(led_b,HIGH);
delay(preheat_time);
//Isıma işlemi için gereken 5sn süre tamamlandığında mavi LED'i söndürüyoruz:
digitalWrite(led_b,LOW);
delay(600);
}

void loop()
{
  myBluetooth.println();
//analogRead() fonksiyonu ile sensör değerini ölçüyoruz ve bir değişken içerisinde tutuyoruz:
int sensorValue = analogRead(sensor_pin);
int yangin=digitalRead(alev_sensor);
//Sensör değeri belirlediğimiz eşik değerinden yüksek ise alarm() fonksiyonunu çağırıyoruz:
if (sensorValue >= esikdeger)
{
  alarm(100);
   myBluetooth.println("GAZ SIZINTISI ALGILANDI..!!");
   
}
else if(yangin==LOW)
{
  alarm(100);
  myBluetooth.println("ALEV ALGILANDI..!!");
  
}
//Alarmın çalmadığı durumda LED'in yeşil yanmasını istiyoruz:
else{
digitalWrite(led_g, HIGH);
 myBluetooth.print("DURUM NORMAL:");
  myBluetooth.println(sensorValue);
}
//Sensör değerini bilgisayarımızdan görebilmek için seri monitöre yazıyoruz:
Serial.println(sensorValue);
delay(20);
}

//Alarm fonksiyonumuzu tanımlıyoruz. Bu fonksiyon parametre olarak buzzerın ötüp ve LED'in yanıp söneceği süreyi almakta.

void alarm(unsigned int sure)
{
//Buzzer'ın 440Hz'te (la notası) ses üretmesini istiyoruz:
tone(buzzer_pin, 440);
//Normal durumda yeşil yanmakta olan LED'i söndürüp kırmızı renkte yakıyoruz:
digitalWrite(led_r, HIGH);
digitalWrite(led_g, LOW);
delay(sure);
for(int i=0; i<5; i++){
    digitalWrite(ledler[i], HIGH);
    delay(50);
    digitalWrite(ledler[i], LOW);
  }

  for(int j=5; j>0; j--){
    digitalWrite(ledler[j], HIGH);
    delay(50);
    digitalWrite(ledler[j], LOW);
  }
noTone(buzzer_pin);
digitalWrite(led_r, LOW);
digitalWrite(led_g, LOW);
delay(sure);
}
