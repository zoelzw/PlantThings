#include <Wire.h>
#include <ArduinoJson.h>     // Library to format data as JSON


void setup() {
    Serial.begin(115200);  // Start serial communication
    Wire.begin();  // Initialize the first I2C bus
   

    // Simulated setup (no actual sensor initialization needed)
    Serial.println("Using Dummy Data!");
}

void loop() {
    // Simulate dummy data for temperature, humidity, and CO2
    float temp = 22.5;      // Example temperature in Celsius
    float humidity = 55.0;  // Example humidity in percentage
    float co2 = 400.0;      // Example CO2 level in ppm

    // Create a JSON object to store the dummy data
    StaticJsonDocument<256> jsonDoc;
    jsonDoc["temp"] = temp;
    jsonDoc["humidity"] = humidity;
    jsonDoc["co2"] = co2;

    // Serialize JSON to string and send over Serial
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    Serial.println(jsonString);

   

    delay(1000);  // Delay for 1 second before sending the next dummy data
}
