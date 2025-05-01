#ifndef LIZARD_LOUNGE_H
#define LIZARD_LOUNGE_H

// ============ LIBRARIES ============ // 
#include <Wire.h>
#include <elapsedMillis.h>
#include <Server.h>
#include <Adafruit_AHTX0.h>
#include <PubSubClient.h>

// ============ PERIPHERAL SET UP ============ // 
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

// Extern tells the compiler that this variable is declared in another header somewhere else
// Allows the Lizard_Lounge code to use these variables without including the entirety of Sensors.h
extern TwoWire I2C_1;
extern TwoWire I2C_2;
extern Adafruit_AHTX0 aht1;
extern Adafruit_AHTX0 aht2;
extern float UVindex;
extern int waterLevel;

extern void getPeripheralData();
extern void getThresholdData();
extern void sendTempData();
extern void sendSensorData();

extern void getPeripheralData();
extern void getThresholdData();
extern void sendTempData(float temperature_cool, float humidity_cool, float temperature_hot, float humidity_hot);
extern void sendSensorData(float UVindex, int waterLevel);
extern void readAllSensors();

extern void callback(char* topic, byte* payload, unsigned int length);
extern const char* mqtt_server;
extern PubSubClient pubClient;

extern const unsigned long sensorDuration;
extern elapsedMillis sensorTimer;

// UV
#define uvVoltagePin 42
#define uvInputPin 6

// Ultrasonic (Water lvl sensor)
#define trigPin 41
#define echoPin 40

// -- Structures -- //
struct Device {
  String name;
  int pin;
  int mode; // INPUT/OUTPUT
  bool PMOS;   // On HIGH => LOW
  bool active;
};

// -- Setting up devices -- //

// Device device_name = {device.name, DEVICE_GPIO, INPUT/OUTPUT, PMOS?, ACTIVE?};
Device fan = {"fan", FAN_GPIO, OUTPUT, true, false};
Device pump = {"pump", PUMP_GPIO, OUTPUT, true, false};
Device relay1 = {"relay1", RELAY1_GPIO, OUTPUT, false, false}; // Heat lamp
Device relay2 = {"relay2", RELAY2_GPIO, OUTPUT, false, false}; // UV
Device relay3 = {"relay3", RELAY3_GPIO, OUTPUT, false, false}; // CHE
Device extra = {"extra", EXTRA_GPIO, OUTPUT, false, false}; // This is PMOS, but we want it initialized as high
Device trig = {"trig", trigPin, OUTPUT, false, false};
Device echo = {"echo", echoPin, INPUT, false, false}; // must be INPUT

Device devices[] = {fan, pump, relay1, relay2, relay3, extra, echo, trig};

// ============ FEEDBACK VARIABLES ============ // 

extern const unsigned long sensorDuration;
extern elapsedMillis sensorTimer;

// Modes for feedback
enum Mode {
  IDLE,
  DEHUMIDIFY,
  HUMIDIFY,
  TEMPHOT,
  TEMPLOW
};

Mode currentMode = IDLE;
Mode nextMode = IDLE;


// ============ WIFI CONTROL ============ // 

int wifiCheck = 0;

const unsigned long pubDuration = 10000; // How often to retry connection (5 seconds)
elapsedMillis pubTimer = pubDuration;

const unsigned long wifiDuration = 10000; // How often to retry connection (5 seconds)
elapsedMillis wifiTimer = wifiDuration;

#endif