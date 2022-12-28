add_executable(wifi_test2 wifi_test2.cpp)
target_compile_definitions(wifi_test2 PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        )

target_include_directories(wifi_test2 PRIVATE ../include)
target_link_libraries(wifi_test2
        pico_cyw43_arch_lwip_threadsafe_background
        pico_stdlib
        )
pico_add_extra_outputs(wifi_test2)
pico_enable_stdio_usb(wifi_test2 1)

