#include <elio.h>
// HC-SR04 초음파 센서와 Arduino를 사용한 거리 측정 코드

// 핀 번호 설정
const int trigPin = 9;  // Trig 핀
const int echoPin = 10; // Echo 핀

int getDistance()
{
    // 초음파 신호 전송
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Echo 핀으로부터 시간 측정
    long duration = pulseIn(echoPin, HIGH);

    // 시간(duration)을 거리(cm)로 변환
    long distance = duration * 0.034 / 2;

    // 측정된 거리 출력
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;
}

void setup()
{
    // 시리얼 통신 시작
    Serial.begin(115200);

    // 핀 모드 설정
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void forward()
{
    sendDCS(30, 30);
    delay(100);
}

void back()
{
    sendDCS(-30, -30);
    delay(500);
}

void left()
{
    sendDCS(0, 30);
    delay(500);

}

void right()
{
    sendDCS(30, 0);
    delay(500);
}

void stop()
{
    sendDCS(0, 0);
    delay(100);
}

void loop()
{
    long distance = getDistance();

    if ( distance >= 40)
    {
        forward();
    }
    else if (distance < 40)
    {
        back();
        right();
    }
}
