#include <DHT.h>

// DHT 센서 유형 및 핀 설정
#define DHTPIN 2      // DHT11 데이터 핀이 연결된 Arduino 핀
#define DHTTYPE DHT11 // DHT11 센서 유형

// DHT 객체 생성
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    Serial.println(F("DHT11 온습도 센서 예제"));

    dht.begin();
}

void loop()
{
    // 측정값 읽기 전 잠시 대기
    delay(2000);

    // 온도와 습도 값 읽기
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // 값이 유효한지 확인
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("센서에서 값을 읽을 수 없습니다!"));
        return;
    }

    // 시리얼 모니터에 값 출력
    Serial.print(F("습도: "));
    Serial.print(h);
    Serial.print(F("%  온도: "));
    Serial.print(t);
    Serial.println(F("°C"));
}
