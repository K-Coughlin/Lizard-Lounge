// State variables for non-blocking temperature and humidity readings
enum TempHumidState { SENSOR1_READ, SENSOR1_DELAY, SENSOR2_READ, SENSOR2_DELAY, DONE };
TempHumidState thState = SENSOR1_READ;

elapsedMillis thTimer;  // Timer for managing delays in temphumidControl
const unsigned int sensorDelay = 500; // 2-second delay for sensor stabilization
const unsigned int cloudUpdateDelay = 250; // 500ms delay for cloud update

void temphumidControl() {
    switch (thState) {
    case SENSOR1_READ:
        // Read and print temperature and humidity from the first AHT20 sensor
        sensors_event_t humidity1, temp1;
        aht1.getEvent(&humidity1, &temp1);

        Serial.println("Sensor 1 - Temperature: " + String(temp1.temperature) + " °C");
        Serial.println("Sensor 1 - Humidity: " + String(humidity1.relative_humidity) + " %");

        // Store variables for later use
        temperature_cool = float(temp1.temperature);
        humidity_cool = int(humidity1.relative_humidity);

        thTimer = 0;  // Reset the timer
        thState = SENSOR1_DELAY;
        break;

    case SENSOR1_DELAY:
        if (thTimer >= sensorDelay) {
            thState = SENSOR2_READ;
        }
        break;

    case SENSOR2_READ:
        // Read and print temperature and humidity from the second AHT20 sensor
        sensors_event_t humidity2, temp2;
        aht2.getEvent(&humidity2, &temp2);

        Serial.println("Sensor 2 - Temperature: " + String(temp2.temperature) + " °C");
        Serial.println("Sensor 2 - Humidity: " + String(humidity2.relative_humidity) + " %");

        // Store variables for later use
        temperature_hot = float(temp2.temperature);
        humidity_hot = int(humidity2.relative_humidity);

        thTimer = 0;  // Reset the timer
        thState = SENSOR2_DELAY;
        break;

    case SENSOR2_DELAY:
        if (thTimer >= cloudUpdateDelay) {
            // Update variables for Web App
            ArduinoCloud.update();
            thTimer = 0;  // Reset the timer
            thState = DONE;
        }
        break;

    case DONE:
        Serial.println("Done reading sensors!");
        thState = SENSOR1_READ; // Reset state for the next cycle
        break;
    }
}
