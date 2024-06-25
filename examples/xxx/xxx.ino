/*****************************************
Eleparts Geunino Stater Kit
Connection:
VCC => 5V
GND => GND
OUTPUT => Pin 8
****************************************/
int DHpin = 2; // Data Pin 8번 설정
byte dat[5];
byte read_data()
{
    byte data;
    for (int i = 0; i < 8; i++)
    {
        if (digitalRead(DHpin) == LOW)
        {
            while (digitalRead(DHpin) == LOW)
                ; // 50us 대기
            delayMicroseconds(30);
            if (digitalRead(DHpin) == HIGH)
                data |= (1 << (7 - i)); // 비트 하나씩 데이터 전송
            while (digitalRead(DHpin) == HIGH)
                ; // data '1 ', 다음 수신을 대기
        }
    }
    return data;
}
void start_test()
{
    digitalWrite(DHpin, LOW); // 센서 감지, 시작신호를 보낸다
    delay(30);                // 지연시간이 18ms 이상으로 DHT11 신호를 감지할수 있음
    digitalWrite(DHpin, HIGH);
    delayMicroseconds(40); // DHT11 응답 대기
    pinMode(DHpin, INPUT);
    while (digitalRead(DHpin) == HIGH)
        ;
    delayMicroseconds(80); // DHT11 응답, 80us 딜레이

    while (digitalRead(DHpin) == LOW)
        ;
    delayMicroseconds(80); // DHT11 버스가 데이터 전송을 한후 80us딜레이
    for (int i = 0; i < 4; i++)
        dat[i] = read_data();
    pinMode(DHpin, OUTPUT);
    digitalWrite(DHpin, HIGH);
}
void setup()
{
    Serial.begin(9600);
    pinMode(DHpin, OUTPUT);
}
void loop()
{
    start_test();
    Serial.print("Current humdity =");
    Serial.print(dat[0], DEC); // 습도 비트를 정수로 디스플레이
    Serial.print('.');
    Serial.print(dat[1], DEC); // 소수 자릿수 디스플레이
    Serial.println('%');
    Serial.print("Current temperature =");
    Serial.print(dat[2], DEC); // 온도 비트를 정수로 디스플레이
    Serial.print('.');
    Serial.print(dat[3], DEC); // 소수 자릿수 디스플레이
    Serial.println('C');
    delay(700);
}
