#include <feedbackLoop.h>

// Function to read all sensors simultaneously: UV, Water Level, Temperature & Humidity sensors
// Sends data to server after reading.
void readAllSensors() {
    readTempSensors();
    readWaterLevelSensor();
    readUV();
    if (wifiCheck) {
      sendSensorData(UVindex, waterLevel);
    }

    // UV & WATER LVL SENSOR CODE
    testUVWater = millis()-testUVWaterStart;
    if (testUVWater >= tooHotDuration) {  // Change this later
      if (waterLevel < 10) {
        pubClient.publish("esp32/useralerts","Water level low! Replace water.");
      }
      if (UVindex == 0 ) {
        pubClient.publish("esp32/useralerts","UV is low!");
      }
      testUVWaterStart = millis();
    }

}

// Helper function to turn on and off peripherals for feedback. Tells server when peripherals actived/deactivated.
void peripheralChange(Device& device, String change) {
  if (device.PMOS) {
      digitalWrite(device.pin, change.equals("on") ? LOW : HIGH);
  } else {
    digitalWrite(device.pin, change.equals("on") ? HIGH : LOW);
  }

  device.active = (change.equals("on") ? true : false);

  // Tell server a peripheral was changed (for SQL chart)a

  // Create JSON string msg for server to jsonify & parse
  String msg = "{\"" + device.name + "\":\"" + change + "\"}";

  // Publish msg
  pubClient.publish("esp32/devices", msg.c_str());
  
}


// Decide next mode for main loop
// ============================================================ ONLY CONSIDERS CERTAIN SIDES. CHANGE LATER =============================================== //
void decideNextMode() {

  if ((humidity_cool > hi_humid_threshold) || (humidity_cool <= lo_humid_threshold)) { 
    // Dehumidification started. We want this to last until it reaches the lowest threshold
    nextMode = DEHUMIDIFY; Serial.println("CurrentMode is dehumidify"); 
    

    }
  else if ((humidity_hot < lo_humid_threshold) || (humidity_hot <= hi_humid_threshold)) {
     nextMode = HUMIDIFY; Serial.println("CurrentMode is humidify"); 
    } 
  else { 
    nextMode = IDLE; Serial.println("CurrentMode is IDLE");
  }

 tempHotChange = temperature_hot > hot_temp_threshold ? true : false;
 tempCold = temperature_hot < low_temp_threshold ? true : false;

// Double check that peripherals are turned off even if cut off before their pre-set times
if (currentMode != nextMode) {
  Serial.println("Switching modes: " + String(modeToString(currentMode)) + " -> " + String(modeToString(nextMode)));
    if (currentMode == DEHUMIDIFY) {
      peripheralChange(fan, "off");
      Serial.println("Fan no longer needed. Turning off..");
    }
    if (currentMode == HUMIDIFY) {
      peripheralChange(pump, "off");
      Serial.println("Pump no longer needed. Turning off..");
    }
  }

  // If its no longer hot, make sure relay is off
  if (tempHotChange && !tempHot){
    if (relay3.active){
      peripheralChange(relay3, "off");
    }
    // Double check that panic bulb is turned back on if its not too too hot
    if (!relay1.active) {
      peripheralChange(relay1, "on");
    }
  }
  tempHot = tempHotChange;
  currentMode = nextMode;
}
// float hot_temp_threshold = 100;
// float low_temp_threshold = 50;
// float hi_humid_threshold = 51;
// float lo_humid_threshold = 29;


// extern float temperature_hot;
// extern int humidity_hot;
// extern float temperature_cool;
// extern int humidity_cool;

// Main feedback loop
void feedbackLoop() {
  
  switch (currentMode) {

    // IDLE: Do nothing mode
    case IDLE:
      break;

    case HUMIDIFY:
      // Is pump already on?
      if (pump.active) {
        //pumpTimer = millis() - pumpStart;
        //if (pumpTimer >= pumpDuration) {
          //Serial.println("Turning pump off, threshold is reached.");
          //peripheralChange(pump, "off");
          //currentMode = IDLE;
        //}
        //Serial.println("Keeping pump on..");
      } else {
        // Pump not already on, turn it on
        peripheralChange(pump, "on");
        pump.active = true;
        //pumpStart = millis();
      }
      break;

    case DEHUMIDIFY:
      // Is fan already on?
      if (fan.active) {
        //fanTimer = millis() - fanStart;
        //if (fanTimer >= fanDuration) {
          //Serial.println("Turning fan off.");
          //peripheralChange(fan, "off");
          //currentMode = IDLE;
        //}
        //Serial.println("Keeping fan on..");
      } else {
        // fan not already on, turn it on
        peripheralChange(fan, "on");
        fan.active = true;
        //fanStart = millis();
      }
      break;
  } // End of switch block

  // Outside switch: Handle temperature overheat case
  if (tempHot) {
    if (!CHEActive) {
      tooHotTimer = millis() - tooHotStart;
      if (tooHotTimer >= tooHotDuration) {
        pubClient.publish("esp32/useralerts", "System is too hot!");
        Serial.println("Device too hot. Send user alert");
        tooHotStart = millis();
        peripheralChange(relay1, "off");
        //currentMode = IDLE;
      }
    } else {
      peripheralChange(relay3, "off");
      Serial.println("Turning off CHE..");
      tooHotStart = millis();
      //currentMode = IDLE;
    }
  }

  // Outside switch: Handle temperature underheat case
    if (tempCold) {
      if (relay3.active) {
        tooColdTimer = millis()-tooColdStart;
        if (tooColdTimer >= tooColdDuration) {
          // USER ALERT
          pubClient.publish("esp32/useralerts","System is too cold!");
          Serial.println("Device too cold. Send user alert");
          tooColdStart = millis();
        // currentMode = IDLE;
        }
      }
      else {
        // Turn on CHE
        // Turn on device
        peripheralChange(relay3, "on");
        Serial.println("Turning on CHE..");
        tooColdStart = millis();
        //currentMode = IDLE;
      }
  }
}


// OLD CASE FOR TEMP HOT AND TEMP LOW
    // case TEMPHOT:
    // // Check if CHE currently already off.
    // if (!CHEActive) {
    //   // If already off and reaches this state, device might be too hot naturally.
    //   // Send user alert if too hot for too long (tooHotDuration)
    //   tooHotTimer = millis()-tooHotStart;
    //   if (tooHotTimer >= tooHotDuration) {
    //     // USER ALERT
    //     pubClient.publish("esp32/useralerts","System is too hot!");
    //     Serial.println("Device too hot. Send user alert");
    //     tooHotStart = millis();
    //     //currentMode = IDLE;
    //   }
    // }
    // else {
    //   // Turn off CHE
    //   // Turn off device
    //   peripheralChange(relay3, "off");
    //   Serial.println("Turning off CHE..");
    //   tooHotStart = millis();
    //   //currentMode = IDLE;
    // }
    // break;

    // case TEMPLOW:
    // // Check if CHE already on
    // // If CHE already on, it may be too cold naturally.
    // // Send user alert if too cold for too long (tooColdDuration)
    // if (relay3.active) {
    //   tooColdTimer = millis()-tooColdStart;
    //   if (tooColdTimer >= tooColdDuration) {
    //     // USER ALERT
    //     pubClient.publish("esp32/useralerts","System is too cold!");
    //     Serial.println("Device too cold. Send user alert");
    //     tooColdStart = millis();
    //    // currentMode = IDLE;
    //   }
    // }
    // else {
    //   // Turn on CHE
    //   // Turn on device
    //   peripheralChange(relay3, "on");
    //   Serial.println("Turning on CHE..");
    //   tooColdStart = millis();
    //   //currentMode = IDLE;
    // }

// Helper function to turn current mode to string:
const char* modeToString(Mode mode) {
  switch (mode) {
    case IDLE:        return "IDLE";
    case DEHUMIDIFY:  return "DEHUMIDIFY";
    case HUMIDIFY:    return "HUMIDIFY";
    case TEMPHOT:     return "TEMPHOT";
    case TEMPLOW:     return "TEMPLOW";
    default:          return "UNKNOWN";
  }
}
