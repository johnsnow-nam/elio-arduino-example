# ElioLibrary

ElioLibrary provides support for the Elio board. It includes various methods to control the hardware features of Elio.

## Installation

To install this library, use the Library Manager in the Arduino IDE or download the ZIP and install it manually.

## Usage

```cpp
#include <elio.h>

void setup(){
          
      Serial.begin(115200);
      Serial.println();
}
void loop(){

  sendIO("IO1", 50);
  delay(500);
  sendIO("IO1", 0);
  delay(500);

  sendServos(90, 0);
  delay(500);
  sendServos(0, 0);
  delay(500);
}


License
This library is licensed under MIT.

#include <Arduino.h>
#include <elio.h>

