//MOTOR


#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>
#include "hardware/adc.h"


uint en = 21;
uint out1 = 17;
uint out2 = 20;
uint sensor_pin = 15;    // Adjust for your sensor pin
uint led_pin=25;
#define SENSOR_PIN 26 
void setup(){
//PUMP
  gpio_init(en); 
  gpio_init(out1); // en
  gpio_init(out2);
  gpio_init(led_pin);
  
  gpio_set_dir(en, GPIO_OUT);
  gpio_set_dir(out1, GPIO_OUT);
  gpio_set_dir(out2, GPIO_OUT);
  gpio_set_dir(led_pin, GPIO_OUT);


//MOISTURE SENSOR
  gpio_init(sensor_pin);
  gpio_set_dir(sensor_pin, GPIO_IN);


    // Enable the internal temperature sensor
    adc_set_temp_sensor_enabled(true);

    // Initialize ADC
    adc_init();
    adc_gpio_init(SENSOR_PIN);

    stdio_init_all();
    // Initialize serial port for debugging
}


int main() {
  setup();

  while (true) {
        //Temp
        // Configure ADC
        adc_set_temp_sensor_enabled(true);
        adc_select_input(4);

        // Read raw ADC value from the temperature sensor
        uint16_t result = adc_read();

        // Conversion factor for ADC to voltage (assuming V_REF is 3.3V)
        const float conversion_factor = 3.3f / (1 << 12);

        // Convert ADC value to voltage
        float voltage = result * conversion_factor;

        // Convert voltage to temperature using the LM35 conversion factor
        float temperature = 27 - (voltage - 0.706) / 0.001721; // LM35 has a 10 mV per degree Celsius scaling
        printf("Temperature:    %.2f degrees           ", temperature);
        // printf("Temp is", temperature);
        bool sensor_state = gpio_get(sensor_pin);
        printf("sensor state: " + sensor_state);
        if (sensor_state && temperature<30) {
            // Sensor is dry,turn on the pump
            gpio_put(en, 1);
            gpio_put(out1, 1);
            gpio_put(out2, 0);
            gpio_put(led_pin, 1);
        } else {
            // Sensor detects moisture, turn on the LED,turn off the pump 
            gpio_put(en, 0);
            gpio_put(led_pin, 0);
        }
        sleep_ms(1000); // Delay for a second
    }

    return 0;
}


