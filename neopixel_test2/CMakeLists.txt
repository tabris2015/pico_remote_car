add_executable(neopixel_test2 neopixel_test2.cpp)
target_include_directories(neopixel_test2 PRIVATE ../include)
target_link_libraries(neopixel_test2 pico_stdlib plasma)
pico_add_extra_outputs(neopixel_test2)
pico_enable_stdio_usb(neopixel_test2 1)

