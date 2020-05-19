#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "elio.h"

void setup(){
          
      Serial.begin(115200);
      Serial.println();
}
void loop(){
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
  sendIO("IO1", 50);
  delay(500);
  sendIO("IO1", 0);
  delay(500);


  sendServo(90, 0);
  delay(500);
  sendServo(0, 0);
  delay(500);



  sendDC(90, 0);
  delay(500);
  sendDC(0, 0);
  delay(500);

}
