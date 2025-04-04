// Create timers
elapsedMillis sensorTimer_UV;
elapsedMillis sensorTimer_WL;

// ============================= HELPER FUNCTIONS ================================== //

// -- UV -- //
void readUV() {

  const unsigned int readInterval_UV = 10000; // 10 seconds

  if (sensorTimer_UV >= readInterval_UV ) {
      // read the value from the UV sensor:
      uvSensorValue = analogRead(uvInputPin); 
      // read the value from the sensor:
      voltageUV =  uvSensorValue * (5.0/1023.0);
      UVindex = voltageUV/0.1;

      Serial.print("UV Index: ");
      Serial.println(UVindex);
      UV = UVindex;
      
      sensorTimer_UV = 0; // Reset timer
    }
}

// -- Water Lvl Sensor -- //
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance;              //send back the distance that was calculated
}

void readWaterLevelSensor() {
  const unsigned int readInterval_WL = 10000; // 10 seconds

  // ********************* TODO: Update /calibrate *********************
  float distanceDifference = 2.61;
  float maxDistance = 3.6;
  float minDistance = 1.4;
  float distance = 0.0;
  float waterLevel = 0.0;

    if (sensorTimer_WL >= readInterval_WL) 
    {
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
      
      delay(50);      //delay 50ms between each reading
      sensorTimer_WL = 0; // Reset timer
    }
}
