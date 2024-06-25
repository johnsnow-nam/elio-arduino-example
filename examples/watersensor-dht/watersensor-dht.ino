#include <elio.h>
#include <DHT.h>
const int sensorPin = A0; // Analog pin A0 connected to the water sensor
// #include <LiquidCrystal_I2C.h>

// I2C LCD 주소와 크기를 설정합니다. (주소는 보드에 따라 다를 수 있습니다)
// LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 주소 0x27, 16x2 크기
// DHT 센서 유형 및 핀 설정
#define DHTPIN 2      // DHT11 데이터 핀이 연결된 Arduino 핀
#define DHTTYPE DHT11 // DHT11 센서 유형

// DHT 객체 생성
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200); // Initialize serial communication
    sendIO("5V", 100);
    dht.begin();
    // LCD 초기화
    // lcd.init();
    // // 백라이트 켜기
    // lcd.backlight();
}

void loop()
{

    int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor

    // Display the sensor value on the Serial Monitor
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);
    // char buffer[32]; // 출력할 문자열을 저장할 버퍼
    // // 숫자를 문자열로 변환
    // sprintf(buffer, "Sensor Value:%d", sensorValue);
    // lcd.setCursor(0, 0); // 첫 번째 줄
    // lcd.print(buffer);

    // Example: Turn on the LED if water level is high (threshold is 500)
    if (sensorValue > 500)
    {
        sendIO("IO1", 100);
        sendIO("IO2", 0);
        sendDC("DC1", 50);
    }
    else
    {
        sendIO("IO2", 100);
        sendIO("IO1", 0);
        sendDC("DC1", 0);
    }

    // 온도와 습도 값 읽기
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // 값이 유효한지 확인
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("센서에서 값을 읽을 수 없습니다!"));
        sendIO("IO3", 100);
        return;
    }

    sendIO("IO3", 0);

    // 시리얼 모니터에 값 출력
    Serial.print(F("습도: "));
    Serial.print(h);
    Serial.print(F("%  온도: "));
    Serial.print(t);
    Serial.println(F("°C"));

    delay(1000); // Wait for 1 second before reading again
}
