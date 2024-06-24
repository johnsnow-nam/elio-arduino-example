#include <SoftwareSerial.h>
#include <elio.h>

SoftwareSerial BTSerial(2, 3);

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  
  // Bluetooth 시리얼 설정
//  BTSerial.begin(9600);  // HC-05 모듈 AT 모드 기본 통신 속도

}

void loop()
{
  // Bluetooth로부터 데이터 수신
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
   sendIO("IO1", 100);
  }
  
  // 시리얼 모니터로부터 데이터 전송
  if (Serial.available()) {
    BTSerial.write(Serial.read());
    sendIO("IO2", 100);
  }
}
