// DHT11 센서를 쉽게 제어하기 위한 라이브러리를 추가합니다. 
#include "DHT.h"
 
// 온습도 센서를 디지털 2번 핀에 연결합니다.
#define DHTPIN 2
#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE); //dht라는 객체를 만듭니다.
 
void setup() {
  Serial.begin(9600);
  dht.begin();
}
 
void loop() {
    delay(2000); //1초 기다라기
  // 습도와 온도값을 측정하고, 제대로 측정되었는지 확인해줍니다.
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
 
  if (isnan(humidity) || isnan(temperature) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  // 온도와 습도값을 시리얼 모니터에 출력해 줍니다.
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
 

}
