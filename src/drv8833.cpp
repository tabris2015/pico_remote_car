//
// Created by pepe on 02-11-22.
//

#include "drv8833.h"

Drv8833::Drv8833(uint enA_pin, uint enB_pin)
:enA_pin(enA_pin), enB_pin(enB_pin)
{
    // init pwm
    slice_num_a = pwm_gpio_to_slice_num(enA_pin);
    slice_num_b = pwm_gpio_to_slice_num(enB_pin);

    channel_a = pwm_gpio_to_channel(enA_pin);
    channel_b = pwm_gpio_to_channel(enB_pin);

    gpio_set_function(enA_pin, GPIO_FUNC_PWM);
    gpio_set_function(enB_pin, GPIO_FUNC_PWM);

    pwm_set_wrap(slice_num_a, TOP);
    pwm_set_wrap(slice_num_b, TOP);

    pwm_set_chan_level(slice_num_a, channel_a, 0);
    pwm_set_chan_level(slice_num_b, channel_b, 0);

    pwm_set_enabled(slice_num_a, true);
    pwm_set_enabled(slice_num_b, true);
}

void Drv8833::write_int16(int16_t pwm) {
    if(pwm < 0) {
        pwm_set_gpio_level(enA_pin, TOP - abs(pwm));
        pwm_set_gpio_level(enB_pin, TOP);
    } else {
        pwm_set_gpio_level(enB_pin, TOP - abs(pwm));
        pwm_set_gpio_level(enA_pin, TOP);
    }
}

void Drv8833::write(float duty_cycle) {
    if (duty_cycle > 1.0f) duty_cycle = 1.0f;
    if (duty_cycle < -1.0f) duty_cycle = -1.0f;
    write_int16((int16_t)(duty_cycle * TOP));
}