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
    // Generate random dummy data within a range
    float temp = random(180, 300) / 10.0;   // Random temperature between 18.0°C and 30.0°C
    float humidity = random(400, 800) / 10.0; // Random humidity between 40.0% and 80.0%
    float co2 = random(350, 1000);           // Random CO2 between 350 ppm and 1000 ppm


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
