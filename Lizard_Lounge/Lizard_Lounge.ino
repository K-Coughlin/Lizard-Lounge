/*
.__  .__                         .___ .__                                      
|  | |__|____________ _______  __| _/ |  |   ____  __ __  ____    ____   ____  
|  | |  \___   /\__  \\_  __ \/ __ |  |  |  /  _ \|  |  \/    \  / ___\_/ __ \ 
|  |_|  |/    /  / __ \|  | \/ /_/ |  |  |_(  <_> )  |  /   |  \/ /_/  >  ___/ 
|____/__/_____ \(____  /__|  \____ |  |____/\____/|____/|___|  /\___  / \___  >
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \/     \/           \/                         \//_____/      \/ 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣢⣭⠓⣶⣶⣯⣽⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⠿⠤⢯⣾⡿⢞⣫⣭⣍⢦⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢤⣦⣾⣯⣵⡾⢟⣫⣵⠾⠛⣉⣤⡌⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣀⣤⣽⢰⣟⣵⠿⢛⣩⣤⣶⣿⣿⣿⡇⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠼⢿⣿⣿⣾⣭⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣝⣛⡙⠛⠿⠻⣿⣿⣿⡿⣿⣿⡿⠛⠇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⢟⣠⣅⣀⣠⣴⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣦⡈⠫⢍⣛⣿⣿⠿⠿⠿⠟⠋⠀⢀⣾⣿⣆⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣿⣿⣿⣿⣶⣄⡈⠉⠉⠁⢀⣀⣀⣀⣴⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣴⣾⣿⣿⣿⣿⣿⣿⢻⣿⣿⣿⣆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣟⠉⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢈⣿⣿⣿⣿⡳⠦⢤⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣷⣦⣙⡻⢿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠁⣸⢯⡿⠿⣮⡻⣄⠀⠈
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠻⣿⠹⣿⢿⠙⣆⠙⠻⠿⠿⠛⠋⠉⠀⠀⠀⠀⣿⠘⡇⠀⠈⠳⡌⢣⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠏⠀⢹⡎⡇⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠐⠀⠀⠀⠰⠀⠁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠇⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
ASCII Art from asciiart.eu⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/


// ============================= LIBRARIES ================================== //

#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <elapsedMillis.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>

// ============================= VARIABLE SETUP ================================== //

// -- Peripherals -- //
#define FAN_GPIO 4
#define PUMP_GPIO 15
#define RELAY1_GPIO 39
#define RELAY2_GPIO 7
#define RELAY3_GPIO 8
#define EXTRA_GPIO 5

// -- Sensors -- //

// Temperature & Humidity
#define TEMP1_SCL 10
#define TEMP1_SDA 11
#define TEMP2_SCL 12
#define TEMP2_SDA 13

// -- WiFi Control -- //
int wifiCheck = 0;

// -- Thresholds --//
float hot_temp_threshold = -1.0;
float low_temp_threshold = -1.0;
float hi_humid_threshold = -1.0;
float lo_humid_threshold = -1.0;

float temperature_hot = 0.0;
int humidity_hot = 0.0;
float temperature_cool = 0.0;
int humidity_cool = 0.0;

// Feedback toggle (for demo)
bool feedback_toggle = false;

// UV & Water level sensor variables
float UV = 0.0;
int water = 0;
float uvSensorValue = 0.0;
float UVindex = 0.0;
float voltageUV = 0.0;

// Define I2C busses
TwoWire I2C_1 = TwoWire(0); 
TwoWire I2C_2 = TwoWire(1); 

// Create sensor instances
Adafruit_AHTX0 aht1; // First AHT20 sensor
Adafruit_AHTX0 aht2; // Second AHT20 sensor

// UV
#define uvVoltagePin 42
#define uvInputPin 6

// Ultrasonic (Water lvl sensor)
#define trigPin 41
#define echoPin 40

// -- Timers -- //
elapsedMillis taskTimer;
unsigned int taskDelay;

// ============================= DEVICE SETUP ================================== //

// -- Structures -- //
struct Device {
  String name;
  int pin;
  int mode; // INPUT/OUTPUT
  bool PMOS;   // On HIGH => LOW
};

Device fan = {"fan", FAN_GPIO, OUTPUT, true};
Device pump = {"pump", PUMP_GPIO, OUTPUT, true};
Device relay1 = {"relay1", RELAY1_GPIO, OUTPUT, false};
Device relay2 = {"relay2", RELAY2_GPIO, OUTPUT, false};
Device relay3 = {"relay3", RELAY3_GPIO, OUTPUT, false};
Device extra = {"extra", EXTRA_GPIO, OUTPUT, false}; // This is PMOS, but we want it initialized as high
Device trig = {"trig", trigPin, OUTPUT, false};
Device echo = {"echo", echoPin, INPUT, false}; //INPUT

Device devices[] = {fan, pump, relay1, relay2, relay3, extra, echo, trig};


// ============================= SETUP ================================== //
void setup() {
  Serial.begin(115200);   // Start serial communication
  // Wait for serial monitor to catch up
  delay(1500); 

  // Initialize all GPIO Pins
  for (auto& device : devices) {
    pinMode(device.pin, device.mode);
    // If the pin is powered via PMOS, initialize it to HIGH rather than LOW to turn off
    digitalWrite(device.pin, device.PMOS ? HIGH : LOW);
  }

  // Initialize I2Cs
  I2C_1.begin(TEMP1_SDA,TEMP1_SCL);
  aht1.begin(&I2C_1);
  I2C_2.begin(TEMP2_SDA,TEMP2_SCL);
  aht2.begin(&I2C_2);

  // DEBUG: Ask user via terminal if we want to connect to server (for easy code testing without server started)
  Serial.println("Start with WiFi? 0. No, if debugging without server, 1. Yes, if debugging with server");
  while (Serial.available() == 0) {
  }

  wifiCheck = Serial.parseInt();

  if (wifiCheck){
    connectToWiFi();
  }
}

// ============================= LOOP ================================== //
void loop() {
  readSensors();
  readWaterLevelSensor();
  readUV();

  if (wifiCheck){
    sendSensorData(UV, water);
    getThresholdData();
    getFeedbackToggle();
    if (feedback_toggle){
      feedbackLoop();
    } else {
      getPeripheralData();
    }
  }

  //feedbackLoop();

  delay(1000);
}

