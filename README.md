# ElioLibrary

ElioLibrary provides support for the Elio board. It includes various methods to control the hardware features of Elio.

## Installation

To install this library, use the Library Manager in the Arduino IDE or download the ZIP and install it manually.

## Usage

```cpp
#include <ElioLibrary.h>

Elio elio;

void setup(){
          
      Serial.begin(115200);
      Serial.println();
}

void loop() {
  elio.doSomething();
  // Additional code
}
License
This library is licensed under MIT.

c
코드 복사

**Example Code (src/ElioLibrary.h):**
```cpp
#ifndef ELIO_LIBRARY_H
#define ELIO_LIBRARY_H

class Elio {
public:
    void begin();
    void doSomething();
};

#endif
Example Code (src/ElioLibrary.cpp):

cpp
코드 복사



#include <Arduino.h>
#include <elio.h>

void setup(){
          
      Serial.begin(115200);
      Serial.println();
}
void _loop(){

  sendIO("IO1", 50);
  delay(500);
  sendIO("IO1", 0);
  delay(500);

  sendServos(90, 0);
  delay(500);
  sendServos(0, 0);
  delay(500);

}
