#include <elio.h>

void setup()
{
    // 시리얼 통신 시작
    Serial.begin(115200);

    decideToUseSensor("ON", "ON", "ON");
}

void loop()
{
    // rotate();
    assembleData();
    int leftSensorValue = getLine1();
    int rightSensorValue = getLine2();

    //sendServo("SV1", -30);
    //delay(10);
    
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

    //sendServo("SV1", 0);
    //delay(10);

    //sendServo("SV1", 30);
    //1 ㅌㅌㅌㅌㅌㅌㅌㅌㅌㅌㅌㅋㅋㅋㅋdelay(10);
    delay(10);

}

void rotate()
{
    int dc1, dc2;
    dc1 = g_dc1;
    dc2 = g_dc2;

    sendDCS(0, 0);
    sendServo("SV1", -30);
    delay(300);
    sendServo("SV1", 0);
    delay(300);
    sendServo("SV1", 30);
    delay(300);
    sendDCS(dc1, dc2);
}/

void forward()
{
    sendDCS(32, -32);
    // delay(30);
}

void back()
{
    sendDCS(-32, 32);
    // delay(500);
}

void left()
{
    sendDCS(-32, -32);
    //delay(200);
}

void right()
{
    sendDCS(32, 32);
    //ㅏ                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             delay(20);
}

void stop()
{
    sendDCS(0, 0);
    // delay(30);
}
