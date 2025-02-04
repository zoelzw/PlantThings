#include <Wire.h>
#include <Adafruit_SCD30.h>  // Library for the SCD30 CO₂ sensor
#include <ArduinoJson.h>     // Library to format data as JSON

#define LED1 0   // PWM 0 top first port of J2
#define LED2 1  // PWM pin for LED 2
#define LED3 10  // PWM 10 bottom port of J2

Adafruit_SCD30 scd30;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    if (!scd30.begin()) {
        Serial.println("Failed to find SCD30 sensor! Check wiring.");
        while (1);
    }
}

void loop() {
    if (scd30.dataReady()) {
        if (!scd30.read()) {
            Serial.println("Error reading SCD30 sensor data!");
            return;
        }
        
        // Create a JSON object with sensor data
        StaticJsonDocument<256> jsonDoc;
        jsonDoc["temp"] = scd30.temperature;
        jsonDoc["humidity"] = scd30.relative_humidity;
        jsonDoc["co2"] = scd30.CO2;

        // Convert JSON object to string and send it over Serial
        String jsonString;
        serializeJson(jsonDoc, jsonString);
        Serial.println(jsonString);
    }

    // Check if there is incoming serial data
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');  // Read incoming command

        StaticJsonDocument<128> jsonInput;
        DeserializationError error = deserializeJson(jsonInput, input);

        if (!error) {
            if (jsonInput.containsKey("led1")) {
                analogWrite(LED1, jsonInput["led1"]);
            }
            if (jsonInput.containsKey("led2")) {
                analogWrite(LED2, jsonInput["led2"]);
            }
            if (jsonInput.containsKey("led3")) {
                analogWrite(LED3, jsonInput["led3"]);
            }
        }
    }

    delay(1000);  // Adjust the delay as needed
}
