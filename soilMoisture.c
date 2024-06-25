//SOIL MOISTURE SENSOR


#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
// Pin definitions
const uint pump_pin = 21 ;       // Adjust for your LED pin
const uint sensor_pin = 20;    // Adjust for your sensor pin

void setup() {
    // Initialize GPIO for LED
    gpio_init(pump_pin);
    gpio_set_dir(pump_pin, GPIO_OUT);

    // Initialize GPIO for moisture sensor
    gpio_init(sensor_pin);
    gpio_set_dir(sensor_pin, GPIO_IN);

    // Initialize serial port for debugging
    stdio_init_all();
}

int main() {
    setup();

    while (true) {
        bool sensor_state = gpio_get(sensor_pin);

        if (sensor_state) {
            // Sensor is dry, turn off the LED,turn on the pump
       
            gpio_put(pump_pin, true);
        } else {
            // Sensor detects moisture, turn on the LED,turn off the pump 
          
            gpio_put(pump_pin, false);
        }
// gpio_put(led_pin,true);
// bool SensorValue= gpio_get(sensor_pin);
//     printf("Sensor Output: %d\n", moisture_level);
        sleep_ms(1000); // Delay for a second
    }

    return 0;
}