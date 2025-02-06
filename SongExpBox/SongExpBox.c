#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21  // GPIO onde o buzzer está conectado
#define LED_GREEN 11
#define LED_RED 13


uint slice_num = 0;


void set_buzzer_frequency(uint buzzer_gpio, uint freq) {
    slice_num = pwm_gpio_to_slice_num(buzzer_gpio);
    
    // Calcular o clock divisor e a contagem para definir a frequência
    uint32_t clock_div = 4;  // Ajuste conforme necessário
    uint32_t wrap = (125000000 / (clock_div * freq)) - 1;

    pwm_set_clkdiv(slice_num, clock_div);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_gpio_level(buzzer_gpio, wrap / 2);  // 50% duty cycle
    pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();

    gpio_set_function(BUZZER_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT); 

    gpio_set_function(LED_GREEN, GPIO_FUNC_SIO);
    gpio_set_dir(LED_GREEN, GPIO_OUT); 

    gpio_set_function(LED_RED, GPIO_FUNC_SIO);
    gpio_set_dir(LED_RED, GPIO_OUT); 

    while (1) {
        // set_buzzer_frequency(BUZZER_PIN, 1000); // Toca 1kHz
        // sleep_ms(1000);
        // set_buzzer_frequency(BUZZER_PIN, 1500); // Toca 1.5kHz
        // sleep_ms(1000);
        // pwm_set_enabled(slice_num, false);
        // sleep_ms(2000);

        
        gpio_put(BUZZER_PIN, 1); 
        gpio_put(LED_GREEN, 1); 
        gpio_put(LED_RED, 0); 
        sleep_ms(1000);
        gpio_put(BUZZER_PIN, 0); 
        gpio_put(LED_GREEN, 0); 
        gpio_put(LED_RED, 1); 
        sleep_ms(1000);

        gpio_put(BUZZER_PIN, 1); 
        gpio_put(LED_GREEN, 1); 
        gpio_put(LED_RED, 0); 
        sleep_ms(1000);
        gpio_put(BUZZER_PIN, 0); 
        gpio_put(LED_GREEN, 0); 
        gpio_put(LED_RED, 1); 
        sleep_ms(1000);

        gpio_put(BUZZER_PIN, 1); 
        gpio_put(LED_GREEN, 1); 
        gpio_put(LED_RED, 0); 
        sleep_ms(1000);
        gpio_put(BUZZER_PIN, 0); 
        gpio_put(LED_GREEN, 0); 
        gpio_put(LED_RED, 1); 
        sleep_ms(1000);

        gpio_put(BUZZER_PIN, 1); 
        gpio_put(LED_GREEN, 1); 
        gpio_put(LED_RED, 0); 
        sleep_ms(1000);
        gpio_put(BUZZER_PIN, 0); 
        gpio_put(LED_GREEN, 0); 
        gpio_put(LED_RED, 1); 
        sleep_ms(1000);
        

    }
}
