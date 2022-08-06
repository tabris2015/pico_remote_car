cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico_remote_car) # <-- Name your project/executable here!

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

# include neopixel lib
include(PicoLED/PicoLed.cmake)
# Add your source files
add_executable(${NAME}
        src/main.cpp # <-- Add source files here!
        )

# Include required libraries
# This assumes `pimoroni-pico` is stored alongside your project
#include(libraries/bitmap_fonts/bitmap_fonts)
#include(libraries/hershey_fonts/hershey_fonts)
#include(libraries/pico_explorer/pico_explorer)
#include(common/pimoroni_bus)

# include(libraries/pico_display/pico_display)
#include(libraries/pico_display/pico_display)
# include(lilygo_tdisplay/lilygo_tdisplay.cmake)
# include(drivers/st7789/st7789)
# include(drivers/analog/analog)
# include(drivers/button/button)
# include(drivers/motor/motor)

# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
        pico_stdlib
        PicoLed
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