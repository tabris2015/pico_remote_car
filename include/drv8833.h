//
// Created by pepe on 02-11-22.
//

#ifndef PICO_REMOTE_CAR_DRV8833_H
#define PICO_REMOTE_CAR_DRV8833_H

#include "pico/stdlib.h"
#include <cmath>
#include "hardware/pwm.h"

#define TOP 4095

class Drv8833 {
public:
    Drv8833(uint enA_pin, uint enB_pin);
    void write_int16(int16_t pwm);
    void write(float duty_cycle);
private:
    uint enA_pin;
    uint enB_pin;
    uint slice_num_a;
    uint channel_a;
    uint slice_num_b;
    uint channel_b;
};


#endif //PICO_REMOTE_CAR_DRV8833_H
