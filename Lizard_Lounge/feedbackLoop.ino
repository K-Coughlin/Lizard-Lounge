void pumpDemo() {
    digitalWrite(pump.pin, LOW); // Turn on pump
    delay(2000);
    digitalWrite(pump.pin, HIGH); // Turn on pump
  
  }
  
  void feedbackLoop() {
    Serial.println(" ---------- FEEDBBACK MODE ACTIVATED ---------- ");
  
    // -- Hot temp is too hot -- //
    if (temperature_hot > hot_temp_threshold) {
      Serial.println("TempHot too high");
      digitalWrite(relay1.pin, LOW); // Turn off light
    // -- Cold temp too cold -- //
    } else if (temperature_hot < hot_temp_threshold) {
      Serial.println("TempHot too low");
      digitalWrite(relay1.pin, HIGH);
      digitalWrite(relay3.pin, HIGH); // Turn on CHE
    }
    if (hi_humid_threshold == -1) {
      // Don't start yet
    } else {
    if (humidity_hot > hi_humid_threshold ) {
      Serial.println("HumidityHot too high");
      digitalWrite(fan.pin, LOW); // Turn on fan
    } else if (humidity_hot < hi_humid_threshold) {
      Serial.println("HumidityHot too low");
      digitalWrite(fan.pin, HIGH); // Turn off fan
      pumpDemo();
    }
    }
  }
  
  // float temperature_hot = 0.0;
  // int humidity_hot = 0.0;
  // float temperature_cool = 0.0;
  // int humidity_cool = 0.0;
  
  // float hot_temp_threshold = 0.0;
  // float low_temp_threshold = 0.0;
  // float hi_humid_threshold = 0.0;
  // float lo_humid_threshold = 0.0;