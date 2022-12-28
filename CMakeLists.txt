cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico_remote_car) # <-- Name your project/executable here!
set(PICO_BOARD pico_w)


include(pimoroni_pico_import.cmake)
include(pico_sdk_import.cmake)


# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# enable exceptions for picoled
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
# Initialize the SDK
pico_sdk_init()

include(common/pimoroni_i2c)
include(common/pimoroni_bus)
include(libraries/pico_explorer/pico_explorer)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(drivers/msa301/msa301)
include(drivers/encoder/encoder)
include(drivers/motor/motor)
include(drivers/button/button)
include(drivers/pwm/pwm)
include(drivers/pid/pid)
include(drivers/plasma/plasma)
include(lib/RF24/CMakeLists.txt)
include(lib/RF24Network/CMakeLists.txt)
include(lib/RF24Mesh/CMakeLists.txt)


## other executables
add_subdirectory(uart_test)
add_subdirectory(motor_test)
add_subdirectory(encoder_test)
add_subdirectory(mpu_test)
add_subdirectory(explorer_test)
add_subdirectory(encoder_pimoroni_test)
add_subdirectory(neopixel_test2)
add_subdirectory(pid_test)
add_subdirectory(robot_test)
add_subdirectory(rf24_test)

## pico W
set(WIFI_SSID "ZTE_2.4G_nPfgdX" CACHE INTERNAL "ssid")
set(WIFI_PASSWORD "yUUSd4Ar" CACHE INTERNAL "pass")
add_subdirectory(wifi_test)
add_subdirectory(wifi_test2)

# include neopixel lib
include(PicoLED/PicoLed.cmake)
# Add your source files
add_executable(${NAME}
        src/main.cpp # <-- Add source files here!
        src/dc_motor.cpp
        )

target_include_directories(${NAME} PRIVATE include)

# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
        pico_stdlib
        PicoLed
        hardware_uart
        hardware_pwm
#        pico_explorer
#        pico_graphics
        # st7789 
        # button 
        # motor 
        # analog
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

## Set up files for the release packages
#install(FILES
#        ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
#        ${CMAKE_CURRENT_LIST_DIR}/README.md
#        DESTINATION .
#        )
#
#set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
#set(CPACK_GENERATOR "ZIP" "TGZ")
#include(CPack)