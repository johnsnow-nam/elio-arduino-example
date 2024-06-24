#include <Wire.h>

// I2C 주소를 스캔합니다.
void setup()
{
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Scanning...");

    for (byte addr = 1; addr < 127; addr++)
    {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0)
        {
            Serial.print("I2C device found at address 0x");
            Serial.println(addr, HEX);
            delay(500);
        }
    }
    Serial.println("Done.");
}

void loop()
{
    // 스캔 후 할 작업이 없습니다.
}
