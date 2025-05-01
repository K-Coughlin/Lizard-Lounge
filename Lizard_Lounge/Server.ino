#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <elapsedMillis.h>

WiFiClient client;
WiFiClient mqttClient;
HTTPClient http;
HTTPClient httpSensor;

PubSubClient pubClient(mqttClient);


// Thresholds
extern float hot_temp_threshold;
extern float low_temp_threshold;
extern float hi_humid_threshold;
extern float lo_humid_threshold;

// ========= WiFi & Server ========= //
const char* ssid = "LizardLounge";
const char* password = "EightChars";
const char* serverURL = "http://192.168.102.186:5000";
const char* mqtt_server = "192.168.102.186";

// ======== Peripheral activation/deactivation ======== //

void connectToWiFi() {
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  } 
  Serial.println("Connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Prints IP to Serial Monitor

}

// Reconnect MQTT
void reconnectMQTT() {
  // Loop until we're reconnected
  if (!pubClient.connected() && WiFi.status() == WL_CONNECTED) {
    // Attempt to connect
    if (pubTimer >= pubDuration) {
      if (pubClient.connect("ESP32Client")) {
        //Serial.println("connected");
        // Subscribe
        pubClient.subscribe("esp32/devices");
        pubClient.subscribe("esp32/thresholds");
      } else {
        Serial.println(" MQTT Failed, Trying again in 5 seconds");
      }
      pubTimer = 0;
    }
  }
}

// Reconnect WiFi
void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    // Is it time to re-attempt connection?
    if (wifiTimer >= wifiDuration) {
      WiFi.begin(ssid, password);
      wifiTimer = 0;
      Serial.println("Connecting to WiFi...");
      }
    } 
  }

// MQTT Callback code
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println("Message received on topic: " + String(topic) + "Payload: " + String(message));

  if (strcmp("esp32/devices",topic) == 0) { 
    peripheralData(payload);
    // MAKE SURE TO SET ACTIVE BOOLEAN HERE!! ADD TO DEVICES?
  }
  if (strcmp("esp32/thresholds",topic) == 0) {
    thresholdData(payload);
  }

}

// Helper functions for MQTT callback code
// Handle peripheral activation/deactivation
void peripheralData(byte* payload) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc,payload);
  Device deviceToChange;
  String status;

  if (error) {
    Serial.println("Failed to parse JSON");
    http.end();
    return;
  }

  JsonObject obj = doc.as<JsonObject>();
  for (JsonPair kv : obj) {
    String dev = kv.key().c_str();
    status = kv.value().as<const char*>();

    for (auto& d: devices) {
      if (d.name.equals(dev)) {
        deviceToChange = d;
        Serial.println(d.name);
      }
    }
  }

  if (deviceToChange.PMOS) {
    digitalWrite(deviceToChange.pin, status.equals("on") ? LOW : HIGH);
  } else {
    digitalWrite(deviceToChange.pin, status.equals("on") ? HIGH : LOW);
  }
  deviceToChange.active = (status.equals("on") ? true : false);
}

// Handle threshold change
void thresholdData(byte* payload) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc,payload);

  String threshold;
  float amount;


  JsonObject obj = doc.as<JsonObject>();
  for (JsonPair kv : obj) {
    threshold = kv.key().c_str();
    amount = kv.value().as<float>();

    if (threshold.equals("hi_humid")) {
      hi_humid_threshold = amount;
    }
    if (threshold.equals("lo_humid")) {
      lo_humid_threshold = amount;
    }
    if (threshold.equals("hot_temp")) {
      hot_temp_threshold = amount;
    }
    if (threshold.equals("low_temp")) {
      low_temp_threshold = amount;
    }
  
  Serial.println("New threshold: ");
  Serial.println(threshold);
  Serial.println("Amount: ");
  Serial.println(amount);
  }
}

// Make vars for this
// Subscribe to esp32/useralerts
// Subscribe server to esp32/useralerts
// Figure out 'alerts' on server

// void checkForUserAlert() {
//   // UV Too Low
//   if (userAlertTimer >= userAlertDuration) {
//     if (waterLvl < 15) {
//       // Publish MQTT
//     }
//     if (UV == 0 && relay2.active) {
//       // Publish MQTt
//     }
//     userAlertTimer = 0;
//   }
// }

// void getPeripheralData() {
//   // This code must be ellapsedmillis or asynch
//     String dataURL = String(serverURL) + "/data";
//     http.begin(client, dataURL);

//     int httpCode = http.GET();

//     if (httpCode == HTTP_CODE_OK) {
//         String payload = http.getString();

//         // ********* Parsing Json ********* //  
//         StaticJsonDocument<200> doc;
//         DeserializationError error = deserializeJson(doc, payload);

//         if (error) {
//             Serial.println("Failed to parse JSON");
//             http.end();
//             return;
//         }

//         // Loop through devices and handle them
//         JsonObject devices_list = doc["devices"];
//         for (auto& device : devices) {
//             String state = devices_list[device.name];
//             // Serial.println(device.name + " state: " + state);

//             if (device.PMOS) {
//                 digitalWrite(device.pin, state == "on" ? LOW : HIGH);
//             } else {
//                 digitalWrite(device.pin, state == "on" ? HIGH : LOW);
//             } 
//         }
//     } else {
//         Serial.println("Error getting payload");
//     }

//     http.end();
// }

// void getThresholdData() {
//     String dataURL = String(serverURL) + "/data";
//     http.begin(client, dataURL);

//     int httpCode = http.GET();

//     if (httpCode == HTTP_CODE_OK) {
//         String payload = http.getString();

//         // ********* Parsing Json ********* //  
//         StaticJsonDocument<200> doc;
//         DeserializationError error = deserializeJson(doc, payload);

//         if (error) {
//             Serial.println("Failed to parse JSON");
//             http.end();
//             return;
//         }

//         // Loop through devices and handle them
//         JsonObject thresholds_list = doc["thresholds"];
//         hot_temp_threshold = float(thresholds_list["hot_temp"]);
//         low_temp_threshold = float(thresholds_list["low_temp"]);
//         hi_humid_threshold = float(thresholds_list["hi_humid"]);
//         lo_humid_threshold = float(thresholds_list["lo_humid"]);
//     } else {
//         Serial.println("Error getting payload");
//     }

//     http.end();
// }

// // void getFeedbackToggle() {
// //     String dataURL = String(serverURL) + "/data";
// //     http.begin(client, dataURL);

// //     int httpCode = http.GET();

// //     if (httpCode == HTTP_CODE_OK) {
// //         String payload = http.getString();

// //         // ********* Parsing Json ********* //  
// //         StaticJsonDocument<200> doc;
// //         DeserializationError error = deserializeJson(doc, payload);

// //         if (error) {
// //             Serial.println("Failed to parse JSON");
// //             http.end();
// //             return;
// //         }

// //         // Loop through devices and handle them
// //         const char* feedback_status = doc["feedback"];
// //         //Serial.println("Feedback Toggle: ");
// //         // feedback_toggle = (strcmp(feedback_status, "on") == 0) ? true : false;
// //         //Serial.println(feedback_toggle);

//     } else {
//         Serial.println("Error getting payload");
//     }

//     http.end();
// }

// Function to send temp data to /update_temps endpoint
void sendTempData(float temp1, float hum1, float temp2, float hum2) {

  // Create JSON payload
  StaticJsonDocument<200> jsonDoc;
  
  jsonDoc["temp1"] = temp1;
  jsonDoc["hum1"] = hum1;
  jsonDoc["temp2"] = temp2;
  jsonDoc["hum2"] = hum2;

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Initialize HTTPClient for /update_temps endpoint
  String dataURL = String(serverURL) + "/update_temps";
  httpSensor.begin(client, dataURL);

  // Set Content-Type header
  httpSensor.addHeader("Content-Type", "application/json");

  // Send POST request
  int httpResponseCode = httpSensor.POST(jsonString);

  // DEBUG
  if (httpResponseCode > 0) {
  //   String response = httpSensor.getString();
  //   Serial.println("Sensor data sent successfully!");
  } else {
    Serial.println("Error sending sensor data: " + httpResponseCode);
  }
  // Close the connection
  httpSensor.end();
}

// Function to send sensor data to /update_temps endpoint
void sendSensorData(float UV, int water) {

  // Create JSON payload
  StaticJsonDocument<200> jsonDoc;
  
  jsonDoc["UV"] = UV;
  jsonDoc["water"] = water;

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Initialize HTTPClient for /update_temps endpoint
  String dataURL = String(serverURL) + "/update_sensors";
  httpSensor.begin(client, dataURL);

  // Set Content-Type header
  httpSensor.addHeader("Content-Type", "application/json");

  // Send POST request
  int httpResponseCode = httpSensor.POST(jsonString);

  // DEBUG
  if (httpResponseCode > 0) {
  //   String response = httpSensor.getString();
  //   Serial.println("Sensor data sent successfully!");
  } else {
    Serial.println("Error sending sensor data: " + httpResponseCode);
  }
  // Close the connection
  httpSensor.end();
}