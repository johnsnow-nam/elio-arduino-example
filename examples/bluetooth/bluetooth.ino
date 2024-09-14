#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // bluetooth module Tx:Digital 10 Rx:Digital 11

void setup()
{

  Serial.begin(115200);
  BTSerial.println("AT+BAUD8");
  BTSerial.begin(9600);
}

void loop()
{    
   // Serial.write("0");
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  if (Serial.available()) {
     Serial.write("2");
      BTSerial.write(Serial.read());
  }
}
