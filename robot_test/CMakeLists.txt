add_executable(robot_test robot_test.cpp ../src/robot.cpp ../src/drv8833.cpp)
target_include_directories(robot_test PRIVATE ../include)
target_link_libraries(robot_test pico_stdlib encoder pid motor button pwm plasma)
pico_add_extra_outputs(robot_test)
pico_enable_stdio_usb(robot_test 1)

