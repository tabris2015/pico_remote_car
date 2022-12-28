add_executable(wifi_test mqtt_test.cpp)
target_compile_definitions(wifi_test PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        )

target_include_directories(wifi_test PRIVATE ../include)
target_link_libraries(wifi_test
        pico_cyw43_arch_lwip_threadsafe_background
        pico_stdlib
        )
pico_add_extra_outputs(wifi_test)
pico_enable_stdio_usb(wifi_test 1)

