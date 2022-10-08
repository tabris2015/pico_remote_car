add_executable(explorer_test neopixel_test.cpp)

target_include_directories(explorer_test PRIVATE ../include)
target_link_libraries(explorer_test pico_stdlib pico_explorer msa301 pico_graphics st7789)
pico_add_extra_outputs(explorer_test)