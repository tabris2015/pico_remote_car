add_executable(rf24_test rf24_test.cpp)
target_include_directories(rf24_test PRIVATE ../include)
target_link_libraries(rf24_test pico_stdlib hardware_spi RF24 RF24Network RF24Mesh)
pico_enable_stdio_usb(rf24_test 1)
pico_enable_stdio_uart(rf24_test 0)

pico_add_extra_outputs(rf24_test)