
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <elio.h>
#include <Arduino.h>

const int8_t  pot_humidity_pin = A0;          // water sensor 를 아날로그 A0 핀에 연결
const int8_t  dht_pin = 2;                     // 온습도 센서를 디지털 2번핀에 연결
const int8_t  dht_type =  DHT11;               // DHT11 센서 유형

LiquidCrystal_I2C lcd(0x27, 16, 2);           // LCD 주소 0x27, 16x2 크기
DHT dht(dht_pin, dht_type);

void setup()
{
 Serial.begin(115200); // Initialize serial communication
  lcd.init();           // LCD 초기화
  lcd.backlight();      //   백라이트 켜기
  dht.begin();
} 

void loop()
{
  int pot_humidity = analogRead(pot_humidity_pin); // 워터센서의 값을 읽어온다.

  Serial.print("pot: ");
  Serial.println(pot_humidity);

  float humidity = dht.readHumidity();    //습도값을 읽어온다.
  float temperature = dht.readTemperature(); //온도값을 읽어온다.

  // 시리얼 모니터에 값 출력
  Serial.print(F("습도: "));
  Serial.print(humidity);
  Serial.print(F("%  온도: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  // 값이 유효한지 확인
  if (isnan(humidity) || isnan(temperature))
  {
    lcd.clear(); // Clear the LCD screen
    lcd.setCursor(0, 0); // Set cursor to the first line
    lcd.print("hdt sensor error");
    Serial.println("hdt sensor error");
    return;
  }

  //LCD에 출력한다.
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); //커서를 첫번째 줄로 이동한다.
  lcd.print("G: ");
  lcd.print(pot_humidity);
  lcd.print(" , T: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1); // 커서를 두번째 줄로 이동한다.
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (pot_humidity < 300){
    sendDC("DC1", 50);
      delay(500);
    sendDC("DC1", 0);
      delay(500);
  }
}
