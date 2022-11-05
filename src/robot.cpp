//
// Created by pepe on 23-10-22.
//

#include "robot.h"

using namespace motor;
using namespace encoder;

Robot::Robot(
        RobotPins pins,
        float max_linear,
        float mix_linear,
        float max_angular,
        float mix_angular,
        float wheel_sep,
        float wheel_r
        )
: l_motor(L_MOTOR_A_PIN, L_MOTOR_B_PIN),
  r_motor(R_MOTOR_A_PIN, R_MOTOR_B_PIN),
  l_encoder(pio0, 0, pin_pair(L_ENCODER_A_PIN, L_ENCODER_B_PIN), PIN_UNUSED, NORMAL_DIR, COUNTS_PER_REV, true),
  r_encoder(pio1, 0, pin_pair(R_ENCODER_A_PIN, R_ENCODER_B_PIN), PIN_UNUSED, NORMAL_DIR, COUNTS_PER_REV, true),
  l_pid(L_VEL_KP, L_VEL_KI, L_VEL_KD, L_UPDATE_RATE),
  r_pid(R_VEL_KP, R_VEL_KI, R_VEL_KD, R_UPDATE_RATE),
  button(BUTTON_PIN),
  max_linear(max_linear),
  min_linear(min_linear),
  max_angular(max_angular),
  min_angular(min_angular),
  wheel_separation(wheel_sep),
  wheel_radius(wheel_r),
  l_setpoint(0),
  r_setpoint(0)
{
    l_encoder.init();
    r_encoder.init();

    l_motor.write(0);
    r_motor.write(0);
    l_setpoint = 0;
    r_setpoint = 0;
}

void Robot::set_unicycle(float v, float w) {
    if(v > max_linear) v = max_linear;
    if(v < min_linear) v = min_linear;
    if(w > max_angular) w = max_angular;
    if(w < min_angular) w = min_angular;

    l_setpoint = (2 * v - w * wheel_separation) / (2 * wheel_radius);
    r_setpoint = (2 * v + w * wheel_separation) / (2 * wheel_radius);
}

void Robot::update() {
    capture();
//    l_capture = l_encoder.capture();
//    r_capture = r_encoder.capture();

    l_pid.setpoint = l_setpoint;
    r_pid.setpoint = r_setpoint;

    float l_input = l_capture.radians_per_second();
    float r_input = r_capture.radians_per_second();

    float l_accel = l_pid.calculate(l_input);
    float r_accel = r_pid.calculate(r_input);

    float l_motor_out = l_accel;//l_motor.speed() + (l_accel * UPDATE_RATE);
    float r_motor_out = r_accel;//r_motor.speed() + (r_accel * UPDATE_RATE);
    l_motor.write(l_motor_out);
    r_motor.write(r_motor_out);

    printf("l_s: %.2f, \tl_i: %.2f, \tlpid_o: %.2f, \tlm_o: %.2f \tr_s: %.2f, \tr_i: %.2f, \trpid_o: %.2f, \trm_o: %.2f\n",
           l_setpoint, l_input, l_accel, l_motor_out,
           r_setpoint, r_input, r_accel, r_motor_out
           );

}

void Robot::set_left(float vel) {
    l_setpoint = vel;
//    l_motor.write(vel);
}
void Robot::set_right(float vel) {
    r_setpoint = vel;
//    r_motor.write(vel);
}

void Robot::set_left16(int16_t vel) {
//    l_setpoint = vel;
    l_motor.write_int16(vel);
}
void Robot::set_right16(int16_t vel) {
//    r_setpoint = vel;
    r_motor.write_int16(vel);
}


uint32_t Robot::get_l_ticks() {
    return l_capture.count();
}

uint32_t Robot::get_r_ticks() {
    return r_capture.count();
}

int32_t Robot::get_l_delta() {
    return l_capture.delta();
}

int32_t Robot::get_r_delta() {
    return r_capture.delta();
}

float Robot::get_l_rad_s() {
    return l_capture.radians_per_second();
}

float Robot::get_r_rad_s() {
    return r_capture.radians_per_second();
}

void Robot::capture() {
    l_capture = l_encoder.capture();
    r_capture = r_encoder.capture();
}
