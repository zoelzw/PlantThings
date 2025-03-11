const int ledPin1 = 23;  // LED connected to pin 9
const int ledPin2 = 22;  // LED connected to pin 0
const int ledPin3 = 1;  // LED connected to pin 1

int pwmValue1 = 128;  // Initial duty cycle for LED on pin 9
int pwmValue2 = 128;  // Initial duty cycle for LED on pin 0
int pwmValue3 = 128;  // Initial duty cycle for LED on pin 1

void setup() {
  // Initialize pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  Serial.begin(9600); // Begin serial communication
  Serial.println("Enter commands to control LEDs:");
  Serial.println("For duty cycle: L,ledNumber,dutyCycle (e.g., L,1,128).");
  Serial.println("For frequency: F,ledNumber,frequency (e.g., F,1,5000).");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any leading/trailing spaces or newlines

    if (input.startsWith("L")) {
      // Parse LED duty cycle command: "L,ledNumber,dutyCycle"
      handleDutyCycleCommand(input);
    } else if (input.startsWith("F")) {
      // Parse LED frequency command: "F,ledNumber,frequency"
      handleFrequencyCommand(input);
    } else {
      Serial.println("Invalid command. Use 'L,ledNumber,dutyCycle' or 'F,ledNumber,frequency'.");
    }
  }

  // Continuously update the brightness
  analogWrite(ledPin1, pwmValue1);
  analogWrite(ledPin2, pwmValue2);
  analogWrite(ledPin3, pwmValue3);

  delay(100); // Small delay to avoid overwhelming serial input
}

void handleDutyCycleCommand(String input) {
  // Format: "L,ledNumber,dutyCycle"
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  
  if (firstComma > 0 && secondComma > firstComma) {
    int ledNumber = input.substring(firstComma + 1, secondComma).toInt();
    int dutyCycle = input.substring(secondComma + 1).toInt();
    
    if (ledNumber >= 1 && ledNumber <= 3 && dutyCycle >= 0 && dutyCycle <= 255) {
      switch (ledNumber) {
        case 1:
          pwmValue1 = dutyCycle;
          analogWrite(ledPin1, pwmValue1);
          Serial.print("Set LED 1 duty cycle to: ");
          Serial.println(pwmValue1);
          break;
        case 2:
          pwmValue2 = dutyCycle;
          analogWrite(ledPin2, pwmValue2);
          Serial.print("Set LED 2 duty cycle to: ");
          Serial.println(pwmValue2);
          break;
        case 3:
          pwmValue3 = dutyCycle;
          analogWrite(ledPin3, pwmValue3);
          Serial.print("Set LED 3 duty cycle to: ");
          Serial.println(pwmValue3);
          break;
      }
    } else {
      Serial.println("Invalid input. Use 'L,ledNumber,dutyCycle' with LED 1-3 and duty cycle 0-255.");
    }
  } else {
    Serial.println("Invalid format. Use 'L,ledNumber,dutyCycle'.");
  }
}

void handleFrequencyCommand(String input) {
  // Format: "F,ledNumber,frequency"
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  
  if (firstComma > 0 && secondComma > firstComma) {
    int ledNumber = input.substring(firstComma + 1, secondComma).toInt();
    int frequency = input.substring(secondComma + 1).toInt();
    
    if (ledNumber >= 1 && ledNumber <= 3 && frequency > 0) {
      switch (ledNumber) {
        case 1:
          analogWriteFrequency(ledPin1, frequency);
          Serial.print("Set LED 1 PWM frequency to: ");
          Serial.println(frequency);
          break;
        case 2:
          analogWriteFrequency(ledPin2, frequency);
          Serial.print("Set LED 2 PWM frequency to: ");
          Serial.println(frequency);
          break;
        case 3:
          analogWriteFrequency(ledPin3, frequency);
          Serial.print("Set LED 3 PWM frequency to: ");
          Serial.println(frequency);
          break;
      }
    } else {
      Serial.println("Invalid input. Use 'F,ledNumber,frequency' with LED 1-3 and a positive frequency.");
    }
  } else {
    Serial.println("Invalid format. Use 'F,ledNumber,frequency'.");
  }
}
