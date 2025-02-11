#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22   
#define LED_PIN 12      
#define PWM_WRAP 20000

// Função configura o PWM e o LED
void configurar_pwm_led() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);  // Habilita a GPIO como PWM para o servo
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);    // Habilita a GPIO como PWM para o LED

    uint slice_servo = pwm_gpio_to_slice_num(SERVO_PIN);
    uint slice_led = pwm_gpio_to_slice_num(LED_PIN);

    pwm_set_clkdiv(slice_servo, 125.0);  // Configura o clock PWM para 50Hz (20ms)
    pwm_set_wrap(slice_servo, PWM_WRAP);
    pwm_set_enabled(slice_servo, true);

    pwm_set_clkdiv(slice_led, 125.0);  // Mesmo clock PWM para o LED
    pwm_set_wrap(slice_led, PWM_WRAP);
    pwm_set_enabled(slice_led, true);
}

// Função define a posição do servomotor e ajusta o brilho do LED
void atualizar_pwm_led(uint slice, uint slice_led, uint16_t pulse_width_us) {
    uint duty_cycle = (pulse_width_us * PWM_WRAP) / 20000;  
    pwm_set_gpio_level(SERVO_PIN, duty_cycle);  

    uint led_brightness = (pulse_width_us - 500) * (PWM_WRAP / 2400); // Mapeia o brilho do LED proporcionalmente ao ângulo do servo
    pwm_set_gpio_level(LED_PIN, led_brightness); // Ajusta o brilho do LED
}

void atualizar_suave(uint slice_servo, uint slice_led, uint16_t start, uint16_t end) {
    int incremento = (end > start) ? 5 : -5; // Define o incremento conforme a direção
    for (int i = start; i != end; i += incremento) {
        atualizar_pwm_led(slice_servo, slice_led, i);
        sleep_ms(10); // Espera para suavizar a movimentação
    }
}

int main() {
    stdio_init_all();   
    configurar_pwm_led();  // Configura PWM e LED

    uint slice_servo = pwm_gpio_to_slice_num(SERVO_PIN);
    uint slice_led = pwm_gpio_to_slice_num(LED_PIN);

    atualizar_pwm_led(slice_servo, slice_led, 2400);
    sleep_ms(5000);

    atualizar_pwm_led(slice_servo, slice_led, 1470);
    sleep_ms(5000);

    atualizar_pwm_led(slice_servo, slice_led, 500);
    sleep_ms(5000);

    while (true) {
        atualizar_suave(slice_servo, slice_led, 500, 2400); // De 0º a 180º
        atualizar_suave(slice_servo, slice_led, 2400, 500); // De 0º a 180º
    }

    return 0;
}