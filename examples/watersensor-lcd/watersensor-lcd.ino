#include <elio.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD 주소와 크기를 설정합니다. (주소는 보드에 따라 다를 수 있습니다)
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 주소 0x27, 16x2 크기
const int sensorPin = A0;           // Analog pin A0 connected to the water sensor

void setup()
{
    Serial.begin(115200); // Initialize serial communication
    // LCD 초기화
    lcd.init();
    // 백라이트 켜기
    lcd.backlight();
}

void loop()
{
    int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor

    // Display the sensor value on the Serial Monitor
    Serial.print("Sensor Value : ");
    Serial.println(sensorValue);

    char buffer[32]; // 출력할 문자열을 저장할 버퍼

    // 숫자를 문자열로 변환
    sprintf(buffer, "Sensor Value:%d", sensorValue);
    lcd.setCursor(0, 0); // 첫 번째 줄
    lcd.print(buffer);

    // Example: Turn on the LED if water level is high (threshold is 500)
    if (sensorValue > 500)
    {
        sendIO("IO1", 100);
        sendIO("IO2", 0);
    }
    else
    {
        sendIO("IO1", 0);
        sendIO("IO2", 100);
    }

    delay(100); // Wait for 1 second before reading again
}
