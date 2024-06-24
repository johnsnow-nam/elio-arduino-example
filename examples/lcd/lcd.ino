

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD 주소와 크기를 설정합니다. (주소는 보드에 따라 다를 수 있습니다)
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 주소 0x27, 16x2 크기

void setup()
{
    Serial.begin(115200);
    // LCD 초기화
    lcd.init();
    // 백라이트 켜기
    lcd.backlight();
    // 화면에 "Hello, World!" 출력
    lcd.setCursor(0, 1); // 첫 번째 줄, 첫 번째 열
    lcd.print("hello");
    //    lcd.clear();
}

void loop()
{
    // 여기에서 반복 동작을 설정할 수 있습니다. (예: 텍스트 업데이트)
}
