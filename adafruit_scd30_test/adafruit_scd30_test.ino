// Basic demo for readings from Adafruit SCD30
#include <Adafruit_SCD30.h>

Adafruit_SCD30  scd30;


void setup(void) {
  Wire1.setSCL(16);
  Wire1.setSDA(17);
  Wire1.begin();

  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit SCD30 test!");
    // Start I2C communication on the second bus (Wire1)
  Wire1.begin(17,16);  // I2C1 pins: SDA=21, SCL=22 (for Teensy 4.x)

  // Initialize the sensor using the second I2C bus
  if (!scd30.begin(Wire1)) {  // Use Wire1 instead of Wire
    Serial.println("Couldn't find the sensor!");
    while (1);
  }
  // // Try to initialize!
  // if (!scd30.begin(I2C1)) {
  //   Serial.println("Failed to find SCD30 chip");
  //   while (1) { delay(10); }
  // }
  Serial.println("SCD30 Found!");


  // if (!scd30.setMeasurementInterval(10)){
  //   Serial.println("Failed to set measurement interval");
  //   while(1){ delay(10);}
  // }
  Serial.print("Measurement Interval: "); 
  Serial.print(scd30.getMeasurementInterval()); 
  Serial.println(" seconds");
}

void loop() {
  if (scd30.dataReady()){
    Serial.println("Data available!");

    if (!scd30.read()){ Serial.println("Error reading sensor data"); return; }

    Serial.print("Temperature: ");
    Serial.print(scd30.temperature);
    Serial.println(" degrees C");
    
    Serial.print("Relative Humidity: ");
    Serial.print(scd30.relative_humidity);
    Serial.println(" %");
    
    Serial.print("CO2: ");
    Serial.print(scd30.CO2, 3);
    Serial.println(" ppm");
    Serial.println("");
  } else {
    //Serial.println("No data");
  }

  delay(100);
}