//
// Created by pepe on 07-10-22.
//
#include "pico/stdlib.h"
#include "ws2812.hpp"

#define NEOPIXEL_PIN 16
using namespace plasma;

constexpr uint SPEED = 5;
constexpr float BRIGHTNESS = 0.4f;
WS2812 led(1, pio1, 0, NEOPIXEL_PIN);

int main() {
    stdio_init_all();
    led.start();
    float hue = 0.0f;
    while(true) {
        hue += (float)SPEED / 1000.0f;
        led.set_hsv(0, hue, 1.0f, BRIGHTNESS);
        sleep_ms(1000 / 50);
    }
}