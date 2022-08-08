#include "pico/stdlib.h"
#include <cmath>
#include "dc_motor.h"

#define M1_PWM_PIN 2
#define M1_ENA_PIN 3
#define M1_ENB_PIN 4

#define M2_PWM_PIN 7
#define M2_ENA_PIN 5
#define M2_ENB_PIN 6

DCMotor motor1(M1_ENA_PIN, M1_ENB_PIN, M1_PWM_PIN);
DCMotor motor2(M2_ENA_PIN, M2_ENB_PIN, M2_PWM_PIN);

uint32_t millis() {
    return to_ms_since_boot(get_absolute_time());
}

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (1) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        motor1.write(-0.5);
        motor2.write(-0.5);
        sleep_ms(300);
        motor1.write(0);
        motor2.write(0);
        sleep_ms(300);
        motor1.write(0.5);
        motor2.write(0.5);
        sleep_ms(300);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        motor1.write(0);
        motor2.write(0);
        sleep_ms(300);
    }
}
