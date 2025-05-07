#include <Arduino.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
    Serial.begin(9600);
}

// Poll for a measurement, keeping the state machine alive.
// Returns true if a measurement is available.
static bool measure_environment(float *temperature, float *humidity) {
    static unsigned long measurement_timestamp = millis();

    // Measure one every four seconds.
    if (millis() - measurement_timestamp > 3000ul) {
        if (dht_sensor.measure(temperature, humidity) == true) {
            measurement_timestamp = millis();
            return(true);
        }
    }

    return(false);
}

void loop() {
    float temperature, humidity;

    // Measure temp and humidity.
    // If the function returns true, a measurement is available.
    if (measure_environment(&temperature, &humidity) == true) {
        Serial.print("Temperature: ");
        Serial.print((temperature * (9.0 / 5.0) + 32), 1);  // Fahrenheit conversion.
        Serial.print(" deg. C, H = ");
        Serial.print(humidity, 1);
        Serial.println("%");
    }
}
