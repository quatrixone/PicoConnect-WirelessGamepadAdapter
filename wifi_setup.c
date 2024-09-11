// wifi_setup.c
#include "pico/cyw43_arch.h"
#include "lwip/netif.h"
#include <stdio.h>

#define WIFI_SSID "Your_SSID"
#define WIFI_PASSWORD "Your_PASSWORD"

void connect_to_wifi() {
    if (cyw43_arch_init()) {
        printf("Failed to initialize WiFi\n");
        return;
    }

    cyw43_arch_enable_sta_mode();
    printf("Connecting to WiFi...\n");

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect to WiFi\n");
        return;
    }

    printf("Connected to WiFi\n");
    printf("IP Address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));
}
