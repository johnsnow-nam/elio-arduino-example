#include <elio.h>

// 두 개의 TCRT5000 센서를 사용한 라인 추적 로봇 예제

// 핀 번호 설정
const int leftSensorPin = 2;  // 왼쪽 TCRT5000의 디지털 출력 핀
const int rightSensorPin = 3; // 오른쪽 TCRT5000의 디지털 출력 핀

void setup()
{
  // 시리얼 통신 시작
  Serial.begin(115200);

  // 센서 핀 모드 설정
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  decideToUseSensor("OFF", "ON", "ON");
}

void loop()
{
  //decideToUseSensor("OFF", "ON", "ON");
  // 센서 값 읽기
  int leftSensorValue = digitalRead(leftSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

  // 센서 값 디버깅 출력
  Serial.print("Left Sensor: ");
  Serial.print(leftSensorValue);
  Serial.print(" | Right Sensor: ");
  Serial.println(rightSensorValue);

  // 선 추적 알고리즘
  if (leftSensorValue == 0 && rightSensorValue == 0)
  {
    forward();
  }
  else if (leftSensorValue == 1 && rightSensorValue == 0)
  {
    // 왼쪽만 라인을 감지 (왼쪽으로 회전)
    left();
  }
  else if (leftSensorValue == 0 && rightSensorValue == 1)
  {
    // 오른쪽만 라인을 감지 (오른쪽으로 회전)
    right();
  }
  else
  {
    // 둘 다 라인을 감지하지 않음 (멈춤)
    stop();
  }
  // 30밀리초 대기
  // delay(30);
}

void forward()
{
  sendDCS(30, 30);
  // delay(30);
}

void back()
{
  sendDCS(-30, -30);
  // delay(500);
}

void left()
{
  sendDCS(0, 30);
  // delay(500);
}

void right()
{
  sendDCS(30, 0);
  // delay(500);
}

void stop()
{
  sendDCS(0, 0);
  // delay(30);
}
