#include "robot.h"

RobotPins pins;
Robot robot(pins);

int main() {
    stdio_init_all();
//    robot.set_left16(1000);
//    robot.set_left(3.14);
//    robot.set_right(3.14);
    sleep_ms(3000);
    uint32_t counter = 0;
    bool flag = false;
    while (true) {
        if (counter % 80 == 0) {
            flag = !flag;
//            robot.set_left(flag ? 3.14 : 6.28);
//            robot.set_right(flag ? 3.14 : 6.28);
            robot.set_unicycle(flag ? 0.3 : 0.6, 0);
        }
        robot.update();
        sleep_ms(UPDATE_RATE * 1000.0f);
        counter++;
    }
}
