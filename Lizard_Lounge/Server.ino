// ========= WiFi & Server ========= //
const char* ssid = "LizardLounge";
const char* password = "EightChars";
const char* serverURL = "http://192.168.102.186:5000";

WiFiClient client;
HTTPClient http;
HTTPClient httpSensor; // For /update_temps endpoint

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

void getPeripheralData() {
    String dataURL = String(serverURL) + "/data";
    http.begin(client, dataURL);

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        // ********* Parsing Json ********* //  
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.println("Failed to parse JSON");
            http.end();
            return;
        }

        // Loop through devices and handle them
        JsonObject devices_list = doc["devices"];
        for (auto& device : devices) {
            String state = devices_list[device.name];
            // Serial.println(device.name + " state: " + state);

            if (device.PMOS) {
                digitalWrite(device.pin, state == "on" ? LOW : HIGH);
            } else {
                digitalWrite(device.pin, state == "on" ? HIGH : LOW);
            } 
        }
    } else {
        Serial.println("Error getting payload");
    }

    http.end();
}

void getThresholdData() {
    String dataURL = String(serverURL) + "/data";
    http.begin(client, dataURL);

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        // ********* Parsing Json ********* //  
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.println("Failed to parse JSON");
            http.end();
            return;
        }

        // Loop through devices and handle them
        JsonObject thresholds_list = doc["thresholds"];
        hot_temp_threshold = float(thresholds_list["hot_temp"]);
        low_temp_threshold = float(thresholds_list["low_temp"]);
        hi_humid_threshold = float(thresholds_list["hi_humid"]);
        lo_humid_threshold = float(thresholds_list["lo_humid"]);
    } else {
        Serial.println("Error getting payload");
    }

    http.end();
}

void getFeedbackToggle() {
    String dataURL = String(serverURL) + "/data";
    http.begin(client, dataURL);

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        // ********* Parsing Json ********* //  
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.println("Failed to parse JSON");
            http.end();
            return;
        }

        // Loop through devices and handle them
        const char* feedback_status = doc["feedback"];
        //Serial.println("Feedback Toggle: ");
        feedback_toggle = (strcmp(feedback_status, "on") == 0) ? true : false;
        //Serial.println(feedback_toggle);

    } else {
        Serial.println("Error getting payload");
    }

    http.end();
}

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