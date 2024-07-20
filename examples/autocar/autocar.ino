#include <elio.h>

void setup()
{
    // 시리얼 통신 시작
    Serial.begin(115200);

    decideToUseSensor("ON", "ON", "ON");
}

void loop()
{

    assembleData();
    int leftSensorValue = getLine1();
    int rightSensorValue = getLine2();

    // 선 추적 알고리즘
    if (leftSensorValue == 1 && rightSensorValue == 1)
    {
        forward();
    }
    else if (leftSensorValue == 0 && rightSensorValue == 1)
    {
        // 왼쪽만 라인을 감지 (왼쪽으로 회전)
        left();
    }
    else if (leftSensorValue == 1 && rightSensorValue == 0)
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
    sendDCS(30, -30);
    // delay(30);
}

void back()
{
    sendDCS(-30, 30);
    // delay(500);
}

void left()
{
    sendDCS(0, -30);
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
