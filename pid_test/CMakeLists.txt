add_executable(pid_test pid_test.cpp ../src/drv8833.cpp)
target_include_directories(pid_test PRIVATE ../include)
target_link_libraries(pid_test pico_stdlib encoder pid motor button pwm)
pico_add_extra_outputs(pid_test)
pico_enable_stdio_usb(pid_test 1)

