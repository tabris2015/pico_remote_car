#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "font8_data.hpp"

using namespace pimoroni;

static int addr = 0x68;

ST7789 display(
        PicoExplorer::WIDTH,
        PicoExplorer::HEIGHT,
        pimoroni::ROTATE_180,
        false,
        get_spi_pins(BG_SPI_FRONT)
        );

PicoGraphics_PenRGB332 graphics(
        display.width,
        display.height,
        nullptr
        );

//#ifdef i2c_default
static void mpu6050_reset() {
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c_default, addr, buf, 2, false);
}
static void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c_default, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    // Now temperature from reg 0x41 for 2 bytes
    // The register is auto incrementing on each read
    val = 0x41;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 2, false);  // False - finished with bus

    *temp = buffer[0] << 8 | buffer[1];
}
//#endif

int main() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    bool led_state = false;


    // init display
    graphics.set_font(&font8);

    Pen BG = graphics.create_pen(120, 40, 60);
    Pen WHITE = graphics.create_pen(255, 255, 255);


    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(20, GPIO_FUNC_I2C);
    gpio_set_function(21, GPIO_FUNC_I2C);
    gpio_pull_up(20);
    gpio_pull_up(21);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(20, 21, GPIO_FUNC_I2C));

    mpu6050_reset();

    int16_t acceleration[3], gyro[3], temp;

    while (1) {
        mpu6050_read_raw(acceleration, gyro, &temp);

        graphics.set_pen(BG);
        graphics.clear();
        graphics.set_pen(WHITE);
        graphics.text("HOLA ACCEL", Point(10, 10), 220);
        char s_buf[60];
        sprintf(s_buf, "Accel: \n%d, %d, %d \nGyro: \n%d, %d, %d \nTemp: %d", acceleration[0], acceleration[1], acceleration[2], gyro[0], gyro[1], gyro[2], temp);
//        std::ostringstream ss;
//        ss << "x: " << acceleration[0] << ", y: " << acceleration[1] << ", z: " << acceleration[2];
//        std::string s(ss.str());
//        graphics.text(s, Point(10, 30), 220);
        graphics.text(s_buf, Point(10, 60), 220);
        display.update(&graphics);
        led_state = !led_state;
        gpio_put(PICO_DEFAULT_LED_PIN, led_state);
        sleep_ms(20);
    }

//#endif
    return 0;
}