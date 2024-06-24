#include <elio.h>

const int sensorPin = A0; // Analog pin A0 connected to the water sensor

void setup()
{
    Serial.begin(115200); // Initialize serial communication
}

void loop()
{
    int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor

    // Display the sensor value on the Serial Monitor
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    // Example: Turn on the LED if water level is high (threshold is 500)
    if (sensorValue > 500)
    {
        sendIO("IO1", 100);
        sendIO("IO2", 0);
    }
    else
    {
        sendIO("IO2", 100);
        sendIO("IO1", 0);
    }

    delay(1000); // Wait for 1 second before reading again
}
