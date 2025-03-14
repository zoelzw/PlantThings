#include <Wire.h>
#include <Adafruit_SCD30.h>  // Library for the SCD30 CO₂ sensor
#include <ArduinoJson.h>     // Library to format data as JSON

const int ledPin1 = 23;
const int ledPin2 = 22;

Adafruit_SCD30 scd30;

int ledPWM1 = 0;
int ledPWM2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);

  while (!Serial) {
    delay(100);  // Wait for serial connection to stabilize
  }

  Serial.println("Nexus SCD 30 + Lights Serial Ready");  // Confirmation message

  Wire.begin();

  if (!scd30.begin(SCD30_I2CADDR_DEFAULT, &Wire1)) {
        Serial.println("Failed to find SCD30 sensor! Check wiring.");
        while (1);
  }
  Serial.println("SCD30 Found!");
  Serial.println("Enter commands to control LEDs:");
  Serial.println("For duty cycle: L,ledNumber,dutyCycle (e.g., L,1,128).");
  //Serial.println("For frequency: F,ledNumber,frequency (e.g., F,1,5000).");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    delay(10);
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any leading/trailing spaces or newlines

    if (input.startsWith("L")) {
      // Parse LED duty cycle command: "L,ledNumber,dutyCycle"
      handleDutyCycleCommand(input);
    } else {
      Serial.println("Invalid command. Use 'L,ledNumber,dutyCycle'");
    }
  }
  if (scd30.dataReady()) {
    if (!scd30.read()) {
      Serial.println("Error reading SCD30 sensor data!");
      return;
    }
        
  // Create a JSON object with sensor data
  JsonDocument jsonDoc;
  jsonDoc["temp"] = scd30.temperature;
  jsonDoc["humidity"] = scd30.relative_humidity;
  jsonDoc["co2"] = scd30.CO2;

  // Convert JSON object to string and send it over Serial
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  Serial.println(jsonString);
  }
  analogWrite(ledPin1, ledPWM1);
  analogWrite(ledPin2, ledPWM2);

}

void handleDutyCycleCommand(String input) {
  // Format: "L,ledNumber,dutyCycle"
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  JsonDocument jsonDoc;
  jsonDoc["Op"] = "LED";
  
  if (firstComma > 0 && secondComma > firstComma) {
    int ledNumber = input.substring(firstComma + 1, secondComma).toInt();
    int dutyCycle = input.substring(secondComma + 1).toInt();
    jsonDoc["led"] = ledNumber;
    jsonDoc["dutyCycle"] = dutyCycle;
    if (ledNumber >= 1 && ledNumber <= 3 && dutyCycle >= 0 && dutyCycle <= 255) {
      switch (ledNumber) {
        case 1:
          ledPWM1 = dutyCycle;
          jsonDoc["success"] = 1;
          break;
        case 2:
          ledPWM2 = dutyCycle;
          jsonDoc["success"] = 1;
          break;
        case 3:
          jsonDoc["success"] = 0;
          break;
      }
    } else {
      jsonDoc["success"] = 0;
    }
  } else {
    jsonDoc["sucess"] = 0;
  }
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  Serial.println(jsonString);
}

