#include <elio.h>

void setup()
{
    // 시리얼 통신 시작
    Serial.begin(115200);
}

void loop()
{
    assembleData();

    char szMsg[64];
    memset(szMsg, 0x00, sizeof(szMsg));

    Serial.println("*****************************************************");
    sprintf(szMsg, "(%d,%d) [%d,%d]  {%d,%d, %d,%d,%d,%d} --> \n", g_dc1, g_dc2, g_sv1, g_sv2, g_io1, g_io2, g_io3, g_io4, g_v3, g_v5);

    Serial.println(szMsg);

    sprintf(szMsg, "\t[%d,%d,%d]  ", g_sonic, g_line1, g_line2);
    Serial.println(szMsg);

    sprintf(szMsg, "\t[%d,%d,%d] \n", g_temperature, g_humidity, g_water);
    Serial.println(szMsg);
    Serial.println("*****************************************************");

    if (g_water < 250)
    {
        sendIO("3V", 100);
        sendDC("DC1", 20);
    }
    else
    {
        sendIO("3V", 0);
        sendDC("DC1", 0);
    }
}
