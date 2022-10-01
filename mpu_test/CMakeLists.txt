add_executable(mpu_test mpu_test.cpp)

target_include_directories(mpu_test PRIVATE ../include)
target_link_libraries(mpu_test
        pico_stdlib
        hardware_pwm
        hardware_i2c
        hardware_uart
        pico_explorer
        msa301
        pico_graphics
        st7789
        )

pico_add_extra_outputs(mpu_test)
