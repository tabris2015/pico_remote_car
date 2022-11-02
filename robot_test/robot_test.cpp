#include "robot.h"

RobotPins pins;
Robot robot(pins);

int main() {
    stdio_init_all();
    robot.set_left16(1000);
    robot.set_right(0.0);
    while (true) {
//        robot.update();
        sleep_ms(UPDATE_RATE * 1000.0f);
    }
}
