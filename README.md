# ElioLibrary

ElioLibrary provides support for the Elio board. It includes various methods to control the hardware features of Elio.

## Installation

To install this library, use the Library Manager in the Arduino IDE or download the ZIP and install it manually.

## Usage

```cpp
#include <Arduino.h>
#include <elio.h>

void setup()
{

    Serial.begin(115200);
}

void loop()
{
    sendDC("DC1", 50);
    delay(500);

    sendDC("DC1", 0);
    delay(500);

    sendDC("DC2", 50);
    delay(500);

    sendDC("DC2", 0);
    delay(500);

    sendDCS(0, 0);
    delay(500);

    sendServo("SV1", 70);
    delay(500);

    sendServo("SV2", 30);
    delay(500);

    sendServos(0, 0);
    delay(500);

    sendIO("IO1", 100);
    delay(500);

    sendIO("IO2", 100);
    delay(500);

    sendIO("IO3", 100);
    delay(500);

    sendIO("IO4", 100);
    delay(500);

    sendIOS(0, 0, 0, 0, 0, 0);
    delay(500);

    sendAllPower(100, 100, 70, 70, 0, 0, 100, 100, 100, 100);
    delay(500);
}


License
This library is licensed under MIT.


