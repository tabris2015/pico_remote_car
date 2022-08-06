#include <stdio.h>
#include "pico/stdlib.h"

#include <PicoLed.hpp>
#include <Effects/Marquee.hpp>
#include <Effects/Stars.hpp>
#include <Effects/Comet.hpp>
#include <Effects/Bounce.hpp>
#include <Effects/Particles.hpp>

#define LED_PIN 23
#define LED_LENGTH 1



int main() {
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // init neopixel
    printf("init neopixel");
    auto neopixel = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_GRB);
    neopixel.setBrightness(32);
    printf("1. Clear the strip!\n");

    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        neopixel.fill(PicoLed::RGB(255, 0, 0));
        neopixel.show();
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        neopixel.fill(PicoLed::RGB(0, 255, 0));
        neopixel.show();
        sleep_ms(500);
    }
}
