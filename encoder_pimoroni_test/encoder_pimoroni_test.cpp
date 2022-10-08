#include "pico/stdlib.h"
#include "stdio.h"
#include "encoder.hpp"
#define CPR 7
#define L_ENCODER_A 6
#define L_ENCODER_B 7
#define R_ENCODER_A 8
#define R_ENCODER_B 9


using namespace encoder;


constexpr float GEAR_RATIO = 50.0F;
constexpr float COUNTS_PER_REV = CPR * GEAR_RATIO * 4;      // counting microsteps
const pin_pair L_ENCODER(L_ENCODER_A, L_ENCODER_B);
const pin_pair R_ENCODER(R_ENCODER_A, R_ENCODER_B);

const pin_pair encoder_pins[] = {L_ENCODER, R_ENCODER};
const char* ENCODER_NAMES[] = {"left", "right"};
const uint NUM_ENCODERS = count_of(encoder_pins);
Encoder *encoders[NUM_ENCODERS];



int main() {
    stdio_init_all();
    encoders[0] = new Encoder(pio0,
                              0,
                              encoder_pins[0],
                              PIN_UNUSED,
                              NORMAL_DIR,
                              COUNTS_PER_REV,
                              true);
    encoders[1] = new Encoder(pio0,
                              1,
                              encoder_pins[1],
                              PIN_UNUSED,
                              NORMAL_DIR,
                              COUNTS_PER_REV,
                              true);

    encoders[0]->init();
    encoders[1]->init();

    while(true) {
        for(auto e = 0u; e < NUM_ENCODERS; e++) {
            printf("%s = %f, %d \t", ENCODER_NAMES[e], encoders[e]->degrees(), encoders[e]->count());
        }
        printf("\n");

        sleep_ms(100);
    }

}
