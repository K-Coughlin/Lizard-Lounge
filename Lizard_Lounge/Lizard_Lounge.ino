#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Stepper.h>
#include <elapsedMillis.h>

elapsedMillis taskTimer;
unsigned int taskDelay;

// ---------------------------== Set pins  ----------------------------- //

const int motorGPIO = 8;
const int pumpGPIO = 15;
const int SDA_temp1 = 13;
const int SCL_temp1 = 12;
const int SDA_temp2 = 11;
const int SCL_temp2 = 10;

// --------------------------- Motor/Pump Control  --------------------------- //
const int stepsPerRevolution = 32;                     // Steps per revolution for the motor
Stepper myStepper(stepsPerRevolution, 39, 40, 41, 42); // Initialize stepper control (ORIGINAL: pins 27, 25, 26, 33, caused boot error)
  
// --------------------------- Sensor Control  --------------------------- //
// Define the I2C buses
TwoWire I2C_1 = TwoWire(0);  // Default I2C bus (GPIO 21, 22)
TwoWire I2C_2 = TwoWire(1);  // Custom I2C bus (GPIO 18, 19)

// Create sensor instances
Adafruit_AHTX0 aht1; // First AHT20 sensor
Adafruit_AHTX0 aht2; // Second AHT20 sensor


// --------------------------- Wi-Fi Control  --------------------------- //
bool start = false;
void doThisOnConnect(){
  Serial.println("Board successfully connected to Arduino IoT Cloud");
  start = true;
}
// ============================= SETUP ================================== //
void setup() {
  Serial.begin(115200);   // Start serial communication
  // Wait for serial monitor to catch up
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, doThisOnConnect);
  
  // Debug messages for Wi-Fi
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // --------------------------- MOSFET Setup  --------------------------- //

  // Set pin modes
  pinMode(2, OUTPUT);
  pinMode(motorGPIO, OUTPUT);     // PMOS for motor
  pinMode(pumpGPIO, OUTPUT);    // PMOS for pump
  digitalWrite(pumpGPIO, HIGH);  // Set pump off at first

  // --------------------------- Sensor Setup  --------------------------- //

  // Initialize the default I2C bus (GPIO 21 for SDA, GPIO 22 for SCL)
  I2C_1.begin(SDA_temp1, SCL_temp1);    // SDA, SCL for the first sensor
  aht1.begin(&I2C_1);     // Initialize first sensor on I2C_1 bus

  // Initialize the second I2C bus (GPIO 18 for SDA, GPIO 19 for SCL)
  I2C_2.begin(SDA_temp2, SCL_temp2);    // SDA, SCL for the second sensor
  aht2.begin(&I2C_2);     // Initialize second sensor on I2C_2 bus

  taskDelay = 1000;
  taskTimer = 0;
}

void loop() {
  if (start != true) {
    ArduinoCloud.update();
    return;
  }
  unsigned long currentMillis = millis();

  if (taskTimer > taskDelay) {
    taskTimer = 0;
    tempLoop();
  } 
  ArduinoCloud.update();
}

void tempLoop() {
  temphumidControl();
}

void onMotorPinChange()  {
  // Add your code here to act upon MotorPin change
  if (motorPin) {
    digitalWrite(2, HIGH);
    digitalWrite(motorGPIO, LOW);
    Serial.println("Motor activated");
    myStepper.setSpeed(700); // Set stepper motor speed

    myStepper.step(2048/8);  // Move motor 45 degrees clockwise

    delay(3000);             // Wait 3 seconds

    myStepper.step(-2048/8); // Move motor 45 degrees counter-clockwise
  }
  else {
    digitalWrite(2, LOW);
    digitalWrite(motorGPIO, HIGH);
    Serial.println("Motor deactivated");
  }

}

void onWaterPumpChange()  {
    if (waterPump) {
    digitalWrite(2, HIGH);
    digitalWrite(pumpGPIO, LOW);
    Serial.println("Water Pump activated");
  }
  else {
    digitalWrite(2, LOW);
    digitalWrite(pumpGPIO, HIGH);
    Serial.println("Water Pump deactivated");
  }
}

