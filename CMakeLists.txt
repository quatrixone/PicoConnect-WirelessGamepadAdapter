cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(controller_emulator)

pico_sdk_init()

add_executable(controller_emulator
    main.c
    wifi_setup.c
    bluetooth_setup.c
    usb_hid_emulation.c
    web_server.c
)

# Include directories
target_include_directories(controller_emulator PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Bluepad32
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/TinyUSB
)

# Link libraries
target_link_libraries(controller_emulator 
    pico_stdlib 
    cyw43_arch_lwip_sta 
    tinyusb 
    Bluepad32
)

pico_enable_stdio_usb(controller_emulator 1)
pico_enable_stdio_uart(controller_emulator 0)

pico_add_extra_outputs(controller_emulator)
