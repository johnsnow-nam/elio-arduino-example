
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <elio.h>
#include <Arduino.h>

const int8_t pot_humidity_pin = A0; // water sensor 를 아날로그 A0 핀에 연결
const int8_t dht_pin = 2;           // 온습도 센서를 디지털 2번핀에 연결
const int8_t dht_type = DHT11;      // DHT11 센서 유형
const int8_t buzzer_pin = 8;

// const int8_t motor_a_n_pin = 10;
// const int8_t motor_a_r_pin = 11;

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 주소 0x27, 16x2 크기
DHT dht(dht_pin, dht_type);

SoftwareSerial BTSerial(7, 8); // bluetooth module Tx:Digital 10 Rx:Digital 11

void setup()
{
  Serial.begin(115200); // Initialize serial communication
  //  lcd.init();           // LCD 초기화
  //  lcd.backlight();      //   백라이트 켜기
  //  dht.begin();

  BTSerial.begin(9600);


//  // AT 모드로 진입
//  BTSerial.print("AT");
//  delay(1000);
//
//  // 상태 확인
//  BTSerial.print("AT+STATE?");
//  delay(1000);



  //  pinMode(buzzer_pin, OUTPUT);

  //  pinMode(motor_a_n_pin, OUTPUT);
  //  pinMode(motor_a_r_pin, OUTPUT);
}

void loop()
{
  //  int pot_humidity = analogRead(pot_humidity_pin); // 워터센서의 값을 읽어온다.

  //  analogWrite(motor_a_n_pin, 0);
  //  analogWrite(motor_a_r_pin, 255);

  //  Serial.print("pot: ");
  //  Serial.println(pot_humidity);
  //
  //  float humidity = dht.readHumidity();       // 습도값을 읽어온다.
  //  float temperature = dht.readTemperature(); // 온도값을 읽어온다.

  // 시리얼 모니터에 값 출력
  //  Serial.print(F("습도: "));
  //  Serial.print(humidity);
  //  Serial.print(F("%  온도: "));
  //  Serial.print(temperature);
  //  Serial.println(F("°C"));

  // 값이 유효한지 확인
  //  if (isnan(humidity) || isnan(temperature))
  //  {
  //    lcd.clear();         // Clear the LCD screen
  //    lcd.setCursor(0, 0); // Set cursor to the first line
  //    lcd.print("hdt sensor error");
  //    Serial.println("hdt sensor error");
  //    return;
  //  }

  // LCD에 출력한다.
  //  lcd.clear();         // Clear the LCD screen
  //  lcd.setCursor(0, 0); // 커서를 첫번째 줄로 이동한다.
  //  lcd.print("G: ");
  //  lcd.print(pot_humidity);
  //  lcd.print(" , T: ");
  //  lcd.print(temperature);
  //  lcd.print(" C");
  //  lcd.setCursor(0, 1); // 커서를 두번째 줄로 이동한다.
  //  lcd.print("H: ");
  //  lcd.print(humidity);
  //  lcd.print(" %");

  //   char data = 'A'; // 송신할 데이터

  // 데이터 송신
  //   BTSerial.write(data);

  //  if (pot_humidity < 300)
  //  {
  //    digitalWrite(buzzer_pin, HIGH);
  //    delay(10);
  //    digitalWrite(buzzer_pin, LOW);
  //  }
  //  else
  //  {
  //    digitalWrite(buzzer_pin, HIGH);
  //    delay(2);
  //    digitalWrite(buzzer_pin, LOW);
  //  }

  if (BTSerial.available())
  {

    String response = BTSerial.readString();
    Serial.println("Response from HC-10: " + response);



    // 연결 상태에 따른 처리
    if (response.indexOf("CONNECTED") >= 0) {
      Serial.println("HC-10 is connected to a master device.");
    }
  }

  if (Serial.available())
  {
    BTSerial.print(Serial.readString());
  }

  //

  ////  BTSerial.write(pot_humidity);
  //  BTSerial.write(" , T: ");
  ////  BTSerial.write(temperature);
  //  BTSerial.write(" C");
  //  BTSerial.write("H: ");
  ////  BTSerial.write(humidity);
  //  BTSerial.write(" %");
  //  BTSerial.flush();

  delay(1000);
}
