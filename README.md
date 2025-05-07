# Temperature and Humidity Sensor
Using an Arduino UNO to power a DHT11 Temperature and Humidity Sensor.

**Watch on YouTube**

[![Watch on YouTube](https://i.postimg.cc/X7dc4FMJ/tnh-sensor.jpg)](https://youtu.be/WP-ZnrqNaMw)

## Code
The code is polling every 4 seconds for a temp and humidity readin for a temp and humidity reading.
It ensures a measurement is available and if one is, the temperature and humidity are reported.
```c++
static bool measure_environment(float *temperature, float *humidity) {
    static unsigned long measurement_timestamp = millis();

    if (millis() - measurement_timestamp > 3000ul) {
        if (dht_sensor.measure(temperature, humidity) == true) {
            measurement_timestamp = millis();
            return(true);
        }
    }

    return(false);
}
```

The video shows the temperature in Celsius, but I converted to Fahrenheit after filming.
```c++
Serial.print((temperature * (9.0 / 5.0) + 32), 1);  // Fahrenheit conversion.
```

The project requires the DHT library, this is included in the *lib* directory.