//
// Created by pepe on 17-11-22.
//
/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "tcp_server.h"


int main() {
    stdio_init_all();
    sleep_ms(5000);
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi... with creds: %s \t%s\n", WIFI_SSID, WIFI_PASSWORD);

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    return 0;
}