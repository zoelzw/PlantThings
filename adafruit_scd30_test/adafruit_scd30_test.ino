#include <SparkFun_I2C_Mux_Arduino_Library.h>

// Basic demo for readings from Adafruit SCD30
#include <Adafruit_SCD30.h>


#include <Wire.h>


Adafruit_SCD30  scd30;


void setup(void) {
  //TwoWire I2C1 = TwoWire(1); 
  //I2C1.begin(17, 16); // Set SDA and SCL pins for I2C1
  // Wire1.begin(16,17)
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Mux.begin();
  Serial.println("Adafruit SCD30 test!");

    // Start I2C communication on the second bus (Wire1)
  //Wire1.begin(17,16);  // I2C1 pins: SDA=21, SCL=22 (for Teensy 4.x)


  // Try to initialize!
  if (!scd30.begin(SCD30_I2CADDR_DEFAULT, &Wire1)) {
    Serial.println("Failed to find SCD30 chip");
    while (1) { delay(10); }
  }
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