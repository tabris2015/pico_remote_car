//
// Created by pepe on 23-10-22.
//

#ifndef PICO_REMOTE_CAR_ROBOT_H
#define PICO_REMOTE_CAR_ROBOT_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "pico/stdlib.h"
#include "pins.h"
// Pimoroni libs
#include "encoder.hpp"
#include "motor.hpp"
#include "pid.hpp"
#include "button.hpp"
#include "drv8833.h"

using namespace motor;
using namespace encoder;

// How many times to update the motor per second
const uint UPDATES = 40;
constexpr float UPDATE_RATE = 1.0f / (float)UPDATES;

constexpr float GEAR_RATIO = 50.0F;
constexpr float COUNTS_PER_REV = MOTOR_CPR * GEAR_RATIO * 4;
constexpr float SPEED_SCALE = 1.0f;

constexpr float ROBOT_MAX_LINEAR_M_S = 1.0f;
constexpr float ROBOT_MIN_LINEAR_M_S = (-1.0f);
constexpr float ROBOT_MAX_ANGULAR_R_S = 6.28f;
constexpr float ROBOT_MIN_ANGULAR_R_S = (-6.28f);

constexpr float ROBOT_WHEEL_SEPARATION = 0.4f;
constexpr float ROBOT_WHEEL_RADIUS = 0.15f;

// PID values
constexpr float L_VEL_KP = 0.040f;   // Velocity proportional (P) gain
constexpr float L_VEL_KI = 0.06f;    // Velocity integral (I) gain
constexpr float L_VEL_KD = 0.0f;    // Velocity derivative (D) gain
constexpr float R_VEL_KP = 0.040f;   // Velocity proportional (P) gain
constexpr float R_VEL_KI = 0.06f;    // Velocity integral (I) gain
constexpr float R_VEL_KD = 0.0f;    // Velocity derivative (D) gain
constexpr float L_UPDATE_RATE = 1.0f / (float)UPDATES;
constexpr float R_UPDATE_RATE = 1.0f / (float)UPDATES;



struct RobotPins {
    uint led = LED_PIN;
    uint button = BUTTON_PIN;
    uint neopixel = NEOPIXEL_PIN;
    uint l_motor_a = L_MOTOR_A_PIN;
    uint l_motor_b = L_MOTOR_B_PIN;
    uint r_motor_a = R_MOTOR_A_PIN;
    uint r_motor_b = R_MOTOR_B_PIN;
    uint l_encoder_a = L_ENCODER_A_PIN;
    uint l_encoder_b = L_ENCODER_B_PIN;
    uint r_encoder_a = R_ENCODER_A_PIN;
    uint r_encoder_b = R_ENCODER_B_PIN;
};

class Robot {
public:
    Robot(RobotPins pins,
          float max_linear=ROBOT_MAX_LINEAR_M_S,
          float mix_linear=ROBOT_MIN_LINEAR_M_S,
          float max_angular=ROBOT_MAX_ANGULAR_R_S,
          float mix_angular=ROBOT_MIN_ANGULAR_R_S,
          float wheel_sep=ROBOT_WHEEL_SEPARATION,
          float wheel_r=ROBOT_WHEEL_RADIUS);

    void set_unicycle(float v, float w);
    void set_left(float vel);
    void set_right(float vel);
    void set_left16(int16_t vel);
    void set_right16(int16_t vel);
    uint32_t get_l_ticks();
    uint32_t get_r_ticks();

    void update();
    void capture();
    int32_t get_l_delta();
    int32_t get_r_delta();
    float get_l_rad_s();
    float get_r_rad_s();


private:
//    Motor l_motor;
//    Motor r_motor;
    Drv8833 l_motor;
    Drv8833 r_motor;
    Encoder l_encoder;
    Encoder r_encoder;
    PID l_pid;
    PID r_pid;
    Button button;
    float max_linear;
    float min_linear;
    float max_angular;
    float min_angular;
    float wheel_separation;
    float wheel_radius;
    float v;
    float w;
    float l_setpoint;
    float r_setpoint;
    Encoder::Capture l_capture;
    Encoder::Capture r_capture;
};


#endif //PICO_REMOTE_CAR_ROBOT_H
