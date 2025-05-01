#include <Sensors.h>

// ============================= Temperature & Humidity Sensors ================================== //
void readTempSensors() {
    sensors_event_t humidity1, temp1;
    aht1.getEvent(&humidity1, &temp1);

    sensors_event_t humidity2, temp2;
    aht2.getEvent(&humidity2, &temp2);

    float fahrenheit_temp1 = (float(temp1.temperature)*9/5 + 32);
    float fahrenheit_temp2 = (float(temp2.temperature)*9/5 + 32);

    Serial.println("Cool Temperature 1: " + String(fahrenheit_temp1) + " °F");         // COOL SIDE
    Serial.println("Cool Humidity 1: " + String(humidity1.relative_humidity) + " %");  // COOL SIDE
    
    Serial.println("Hot Temperature: " + String(fahrenheit_temp2) + " °F");         // HOT SIDE
    Serial.println("Hot Humidity: " + String(humidity2.relative_humidity) + " %");  // HOT SIDE

    // -- FOR GATHERING DATA -- //
    // Serial.println(String(fahrenheit_temp2) + "," + 
    //            String(humidity2.relative_humidity) + "," + 
    //            String(fahrenheit_temp1) + "," + 
    //            String(humidity1.relative_humidity));

    if (fahrenheit_temp2 - temperature_hot <= -10) {
      // The hot side temperature will not decrease by 10 or more in one reading.
      // If this happens, likely it is a blip in the sensor and it is an innacurate reading.
      // Skip this reading.
      return;
    }

    temperature_hot = fahrenheit_temp2;
    humidity_hot = int(humidity2.relative_humidity);
    temperature_cool = fahrenheit_temp1;
    humidity_cool = int(humidity1.relative_humidity);

    if (wifiCheck){
      sendTempData(temperature_cool, humidity_cool, temperature_hot, humidity_hot);
    }
}

// ============================= UV Sensor ================================== //
void readUV() {
    // read the value from the UV sensor:
    uvSensorValue = analogRead(uvInputPin); 
    // read the value from the sensor:

    // Turn on power pin for UV
    pinMode(42, OUTPUT);
    digitalWrite(42, HIGH);
    voltageUV =  uvSensorValue * (3.3/1023.0);
    UVindex = voltageUV/0.1;

    Serial.print("UV Index: ");
    Serial.println(UVindex);

}

// ============================= Water Level Sensor ================================== //
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);

  //delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance;              //send back the distance that was calculated
}

void readWaterLevelSensor() {
  // ********************* TODO: Update /calibrate *********************
  float distanceDifference = 2.61;
  float maxDistance = 3.6;
  float minDistance = 1.4;
  float distance = 0.0;
  waterLevel = 0.0;

    distance = getDistance();   // Gets Distance in inches

    if (distance >= maxDistance)
    {
      waterLevel = 0;
    }
    else if (distance <= minDistance)
    {
      waterLevel = 100;
    }
    else
    {
      waterLevel = abs(maxDistance - distance)/distanceDifference *100;
    }
    
    // Serial.println("Distance: " + String(distance) + ' in');     // Print the distance that was measured
    // Serial.println("Percent: " + String(waterLevel) + '%');     // Print the percentage that was measured

    Serial.println("Water level: ");
    Serial.println(waterLevel);
    
}