#include <Arduino.h>

#include "elio.h"

void setup()
{

    Serial.begin(115200);
    Serial.println();
}
void loop()
{
    _loop();
}

void _delay(float seconds)
{
    long endTime = millis() + seconds * 1000;
    while (millis() < endTime)
        _loop();
}

void _loop()
{

    //    sendDC("DC1", 0);
    //    delay(1);

    sendIO("IO1", 50);
    delay(500);
    sendIO("IO1", 0);
    delay(500);
    //
    //
    sendServos(90, 0);
    delay(500);
    sendServos(0, 0);
    delay(500);
    //
    //
    //
    //  sendDCS(90, 0);
    //  delay(500);
    //  sendDCS(0, 0);
    //  delay(5);
}
